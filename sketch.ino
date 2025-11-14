#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";

const char* apiEndpoint = "https://SEU-BACKEND-SPRING-NO-AZURE.com/iot/sensordata";

#define STRESS_PIN 34 // BPM
#define NOISE_PIN  35 // Ruído
#define FOCO_PIN   25 // Pushbutton 

bool emFoco = false;
unsigned long tempoInicioFoco = 0;
unsigned long ultimoEnvio = 0;

void setup() {
  Serial.begin(115200);
  pinMode(STRESS_PIN, INPUT);
  pinMode(NOISE_PIN, INPUT);
  pinMode(FOCO_PIN, INPUT_PULLUP); 

  Serial.println("Iniciando simulador Work360 IoT...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConectado ao WiFi!");
}

bool checarBotao() {
  static bool ultimoEstadoBotao = HIGH;
  bool estadoAtualBotao = digitalRead(FOCO_PIN);

  if (estadoAtualBotao == LOW && ultimoEstadoBotao == HIGH) {
    delay(50);
    ultimoEstadoBotao = estadoAtualBotao;
    return true;
  }

  ultimoEstadoBotao = estadoAtualBotao;
  return false;
}

void loop() {
  if (checarBotao()) {
    emFoco = !emFoco;
    if (emFoco) {
      Serial.println("\n*** SESSÃO DE FOCO INICIADA ***");
      tempoInicioFoco = millis();
      ultimoEnvio = millis();
    } else {
      Serial.println("\n*** SESSÃO DE FOCO ENCERRADA ***");
    }
  }

  // Só envia dados se estiver Em Foco e já se passaram 5s desde o último envio
  if (emFoco && (millis() - ultimoEnvio > 5000)) {
    if (WiFi.status() == WL_CONNECTED) {

      // Leitura dos sensores
      int stressValue = analogRead(STRESS_PIN);
      int noiseValue = analogRead(NOISE_PIN);


    // 60 (calmo) - 130 (estresse)
    // 30 (silêncio) - 100 (barulho)
      int batimentos = map(stressValue, 0, 4095, 60, 130);
      int nivelRuido = map(noiseValue, 0, 4095, 30, 100); 

      // Calcula o tempo de foco em segundos
      long tempoFocoSegundos = (millis() - tempoInicioFoco) / 1000;

      // Cria o JSON
      StaticJsonDocument<256> doc;
      doc["usuarioId"] = "user-wokwi-002";
      doc["batimentosCardiacos"] = batimentos;
      doc["nivelRuidoDB"] = nivelRuido;
      doc["tempoFocoSegundos"] = tempoFocoSegundos;

      String jsonPayload;
      serializeJson(doc, jsonPayload);

      // Envia o POST para a API Spring
      HTTPClient http;
      http.begin(apiEndpoint);
      http.addHeader("Content-Type", "application/json");

      Serial.println("\n--- Enviando JSON para a API ---");
      Serial.println(jsonPayload);

      int httpResponseCode = http.POST(jsonPayload);

      if (httpResponseCode > 0) {
        String response = http.getString();
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
      } else {
        Serial.print("Erro no POST. Código: ");
        Serial.println(httpResponseCode);
      }
      http.end();

      ultimoEnvio = millis(); // Marca o tempo do último envio
    }
  }

  delay(10);
}