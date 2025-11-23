# 🚀 Global Solution: Work360 - Módulo IoT

Este repositório contém o código e a documentação para o módulo de Internet das Coisas (IoT) do projeto **Work360**. A solução de IoT foi projetada para capturar dados biométricos e ambientais em tempo real durante as sessões de "Modo Foco" do usuário no aplicativo mobile.

Esses dados são enviados para o backend, onde são processados e utilizados pela Inteligência Artificial Generativa para fornecer insights mais profundos e personalizados sobre a produtividade do usuário, correlacionando o desempenho com fatores do ambiente físico e bem-estar.

Este projeto foi desenvolvido como parte da Global Solution da FIAP, com foco na disciplina **Disruptive Architectures: IOT, IOB & Generative IA**.

---

### 🔗 Repositórios do Ecossistema Work360
- **Mobile (React Native):** [https://github.com/fesilva2109/work360_mobile.git](https://github.com/fesilva2109/work360_mobile.git)
- **Backend (Java/Spring):** [https://github.com/fesilva2109/work360_java.git](https://github.com/fesilva2109/work360_java.git)

---

### 👨‍💻 Integrantes
*   Eduardo Henrique Strapazzon Nagado - RM558158
*   Felipe Silva Maciel - RM555307
*   Gustavo Ramires Lazzuri - RM556772

### 📹 Vídeo de Demonstração
Assista ao vídeo completo do projeto integrado em funcionamento:

▶️ [Work360 - Apresentação da Solução no YouTube](https://youtu.be/-D0v47hslQc?si=L8hpMiDFJNkysrMs)

---

### ✨ Funcionalidades e Integração

O módulo IoT é o coração da coleta de dados do "Internet of Behavior" (IoB) no Work360. Ele se integra diretamente com a funcionalidade **Modo Foco** do aplicativo mobile através do nosso backend.

1.  **Captura de Dados Biométricos (BPM):**
    *   Utiliza um **Pulse Sensor** para medir a frequência cardíaca do usuário.
    *   Esses dados ajudam a IA a correlacionar os níveis de estresse e concentração com as tarefas que estão sendo executadas.

2.  **Monitoramento de Ruído Ambiente:**
    *   Um **Módulo Sensor de Som** mede o nível de ruído no ambiente de trabalho do usuário.
    *   Permite que a IA analise como interrupções sonoras ou um ambiente barulhento afetam a capacidade de concentração e a produtividade.

3.  **Comunicação Segura com o Backend:**
    *   O microcontrolador (ESP32) se conecta à rede Wi-Fi local para enviar os dados coletados.
    *   As leituras dos sensores são enviadas via requisições HTTP POST para um endpoint específico da nossa API Java (`/analytics/iot`).

4.  **Ciclo de Vida Integrado à Sessão de Foco:**
    *   **Início:** Quando o usuário inicia o "Modo Foco" no app mobile, o backend é notificado.
    *   **Monitoramento:** O dispositivo IoT consulta o backend periodicamente para verificar se há uma sessão de foco ativa para o usuário. Ao detectar uma, ele começa a coletar e enviar dados de BPM e ruído a cada poucos segundos.
    *   **Fim:** Quando o usuário para a sessão de foco no app, o dispositivo IoT cessa o monitoramento.
    *   **Análise:** Os dados coletados são armazenados e ficam disponíveis para a IA Generativa, que os utiliza para "enriquecer" os relatórios de produtividade, fornecendo um resumo, insights e recomendações muito mais precisos.

---

### 🏗️ Arquitetura da Solução Integrada

O fluxo de dados demonstra a integração completa entre as disciplinas, desde a interface do usuário até a análise final pela IA.

```
+-------------------------+      +-------------------------+      +--------------------------+
|  App Mobile             |      |  Backend (API Java)     |      |  Dispositivo IoT (ESP32) |
|  (React Native)         |      |  (Spring Boot)          |      |  (C++/Arduino)           |
+-------------------------+      +-------------------------+      +--------------------------+
           |                             |                              |
           | 1. Inicia "Modo Foco"       |                              |
           |---------------------------->|                              |
           |                             | 2. Cria sessão de foco ativa |
           |                             |----------------------------->| (Via polling)
           |                             |                              | 3. Inicia coleta de
           |                             |                              |    BPM e Ruído
           |                             |                              |
           |                             | 4. Envia dados (JSON)        |
           |                             |<-----------------------------|
           |                             |                              |
           | 5. Finaliza "Modo Foco"     |                              |
           |---------------------------->|                              |
           |                             | 6. Finaliza sessão de foco   |
           |                             |----------------------------->| (Via polling)
           |                             |                              |
           | 7. Solicita Relatório com IA|                              |
           |---------------------------->|                              |
           |                             | 8. IA processa dados da      |
           |                             |    sessão (incluindo IoT)    |
           |                             |                              |
           | 9. Retorna Relatório        |                              |
           |<----------------------------|                              |
           |   Enriquecido               |                              |
```

---

### 🛠️ Hardware e Tecnologias

#### Componentes de Hardware
*   **Microcontrolador:** ESP32 (com Wi-Fi integrado)
*   **Sensor de Pulso:** Pulse Sensor Amped
*   **Sensor de Som:** Módulo KY-038
*   **Periféricos:** Protoboard, Jumpers

#### Software e Tecnologias
*   **Linguagem:** C++ (no framework Arduino)
*   **Bibliotecas:**
    *   `WiFi.h`: Para conectividade de rede.
    *   `HTTPClient.h`: Para realizar requisições HTTP para a API.
    *   `ArduinoJson.h`: Para montar o corpo (payload) das requisições em formato JSON.
    *   `PulseSensorPlayground.h`: Para facilitar a leitura do sensor de pulso.
*   **IDE:** Arduino IDE ou PlatformIO (VS Code).

---

### 🚀 Como Executar

#### Pré-requisitos
1.  **Hardware Montado:** O circuito com o ESP32 e os sensores deve estar montado conforme o esquemático.
2.  **Backend Rodando:** O servidor Java do Work360 deve estar em execução na mesma rede Wi-Fi que o ESP32.
3.  **Arduino IDE Configurado:**
    *   Ter o Arduino IDE instalado.
    *   Ter o suporte para a placa ESP32 instalado no Gerenciador de Placas.
    *   Ter as bibliotecas `ArduinoJson` e `PulseSensor Playground` instaladas através do Gerenciador de Bibliotecas.

#### Configuração
1.  **Clonar o Repositório:**
    ```bash
    git clone https://github.com/seu-usuario/work360_iot.git
    cd work360_iot
    ```

2.  **Configurar o Código:**
    *   Abra o arquivo `.ino` principal no Arduino IDE.
    *   Altere as seguintes variáveis para corresponder à sua configuração de rede e backend:

    ```cpp
    // Configurações de Rede
    const char* ssid = "NOME_DA_SUA_REDE_WIFI";
    const char* password = "SENHA_DA_SUA_REDE_WIFI";

    // Endereço do Backend (use o IP local da máquina onde o servidor está rodando)
    String serverName = "http://SEU_IP_LOCAL:8080/analytics/iot";

    // ID do usuário para o qual o dispositivo irá coletar dados
    // (Este ID deve existir no banco de dados)
    const int userId = 1;
    ```

#### Execução
1.  **Conecte o ESP32:** Conecte o dispositivo ESP32 ao seu computador via USB.
2.  **Selecione a Placa e a Porta:** No Arduino IDE, vá em `Ferramentas > Placa` e selecione o modelo do seu ESP32 (ex: "ESP32 Dev Module"). Em `Ferramentas > Porta`, selecione a porta COM correspondente.
3.  **Carregar o Código:** Clique no botão "Carregar" (seta para a direita) para compilar e enviar o código para o dispositivo.
4.  **Monitorar a Saída:** Abra o `Monitor Serial` (ícone de lupa no canto superior direito) com o baud rate configurado para `115200` para ver os logs de conexão, leitura dos sensores e envio de dados para a API.

---

### 💡 Boas Práticas e Cumprimento de Requisitos

*   **Integração Interdisciplinar:** A solução demonstra uma integração real e funcional entre Mobile, Backend e IoT, onde os dados coletados pelo hardware são essenciais para a funcionalidade de IA.
*   **Documentação Clara:** Este README fornece um guia completo sobre a arquitetura, funcionalidades e instruções de execução, cumprindo os requisitos de documentação.
*   **Código Organizado:** O código para o ESP32 é comentado e estruturado para facilitar o entendimento, separando configurações, lógica de sensores e comunicação de rede.
*   **Solução de IA:** Os dados coletados são um insumo primário para a API de IA Generativa no backend, que os utiliza para gerar análises de comportamento (IoB) e produtividade.

