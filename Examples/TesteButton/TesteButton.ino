/*
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "ButtonManager.hpp"

// Configuração do OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

ButtonManager buttonManager;

void setup() {
  Serial.begin(115200);
  
  // Inicializar display OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println("Erro ao inicializar OLED!");
    while(1);
  }
  
  // Tela inicial
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("TESTADOR DE BOTOES");
  display.println("==================");
  display.setCursor(0, 20);
  display.setTextSize(1); 
  display.println("ACQUANATIVA");
  display.setCursor(0, 40);
  display.display();
  
  delay(2000);
}

void loop() {
  buttonManager.update();
  atualizarDisplay();
  delay(50);
}

void atualizarDisplay() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  
  // Cabeçalho
  display.setCursor(0, 0);
  display.println("BOTOES PRESSIONADOS:");
  display.println("-------------------");
  
  // Mostrar estado atual dos botões
  int linha = 16;
  bool algumBotaoPressionado = false;
  
  // Verificar todos os botões dinamicamente
  for(uint8_t i = 0; i < buttonManager.getButtonCount(); i++) {
    uint8_t pin = buttonManager.getButtonPin(i);
    
    if(buttonManager.isPressed(pin)) {
      display.setCursor(0, linha);
      display.print("> ");
      display.print(buttonManager.getButtonName(pin));
      display.setCursor(70, linha);
      display.print("(");
      display.print(buttonManager.getPressCount(pin));
      display.print(")");
      linha += 8;
      algumBotaoPressionado = true;
    }
  }
  
  // Se nenhum botão está pressionado
  if(!algumBotaoPressionado) {
    display.setCursor(0, 20);
    display.setTextSize(2);
    display.println("NENHUM");
    display.setTextSize(1);
  }
  
  // Contador total na parte inferior
  display.setCursor(0, 56);
  display.print("TOTAL: ");
  display.print(buttonManager.getTotalPressCount());
  
  display.display();
}
*/

/**
 * @file symbols_test.cpp
 * @brief Mostra todos os símbolos e caracteres disponíveis no display OLED
 * @details Exibe tabela de caracteres ASCII, símbolos especiais e caracteres gráficos
 */

#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

// Configuração do display OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Variáveis para controle de rolagem
int currentPage = 0;
const int TOTAL_PAGES = 6;
unsigned long lastScrollTime = 0;
const unsigned long SCROLL_DELAY = 5000; // 5 segundos por página

/**
 * @brief Desenha cabeçalho da página
 */
void drawHeader(const char* title) {
    display.clearDisplay();
    
    // Título
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println(title);
    
    // Linha divisória
    display.drawLine(0, 9, 127, 9, SSD1306_WHITE);
    
    // Paginação
    display.setCursor(100, 0);
    display.print(currentPage + 1);
    display.print("/");
    display.print(TOTAL_PAGES);
}

/**
 * @brief Mostra caracteres ASCII básicos (0-127)
 */
void showASCIIBasic() {
    drawHeader("ASCII BASICO (0-127)");
    
    int y = 12;
    int x = 0;
    char buffer[4];
    
    for(int i = 0; i < 128; i++) {
        // Formata o caractere
        if(i < 32) {
            // Caracteres de controle - mostra código
            snprintf(buffer, sizeof(buffer), "%02X", i);
            display.print(buffer);
        } else {
            // Caracteres imprimíveis
            display.write(i);
        }
        
        display.print(" ");
        
        x += 18;
        if(x >= 120) {
            x = 0;
            y += 9;
            display.setCursor(x, y);
        }
        
        // Para se atingir o final da tela
        if(y >= 60) break;
    }
    
    display.display();
}

/**
 * @brief Mostra caracteres ASCII estendidos (128-255)
 */
void showASCIIExtended() {
    drawHeader("ASCII ESTENDIDO (128-255)");
    
    int y = 12;
    int x = 0;
    char buffer[4];
    
    for(int i = 128; i < 256; i++) {
        // Mostra o caractere
        display.write(i);
        snprintf(buffer, sizeof(buffer), "%02X", i);
        display.print(buffer);
        display.print(" ");
        
        x += 24;
        if(x >= 110) {
            x = 0;
            y += 9;
            display.setCursor(x, y);
        }
        
        if(y >= 60) break;
    }
    
    display.display();
}

/**
 * @brief Mostra caracteres especiais e símbolos
 */
void showSpecialSymbols() {
    drawHeader("SIMBOLOS ESPECIAIS");
    
    int y = 12;
    display.setCursor(0, y);
    
    // Símbolos matemáticos
    display.println("Matematicos:");
    display.print("+-*/=<>^~%");
    y += 18;
    
    display.setCursor(0, y);
    display.print("∞≈≠≤≥±√∫∆∂");
    y += 18;
    
    // Símbolos monetários
    display.setCursor(0, y);
    display.println("Moedas:");
    display.print("$€£¥¢");
    y += 18;
    
    // Outros símbolos
    display.setCursor(0, y);
    display.println("Diversos:");
    display.print("©®™°¶§•");
    
    display.display();
}

/**
 * @brief Mostra caracteres gráficos e caixas
 */
void showGraphicCharacters() {
    drawHeader("CARACTERES GRAFICOS");
    
    int y = 12;
    int x = 0;
    
    // Caracteres de bloco
    for(int i = 0xB0; i <= 0xDF; i++) {
        display.write(i);
        display.print(" ");
        
        x += 12;
        if(x >= 120) {
            x = 0;
            y += 9;
            display.setCursor(x, y);
        }
        
        if(y >= 60) break;
    }
    
    display.display();
}

/**
 * @brief Mostra letras internacionais
 */
void showInternationalChars() {
    drawHeader("LETRAS INTERNACIONAIS");
    
    int y = 12;
    display.setCursor(0, y);
    
    // Acentos agudos
    display.println("Acentos Agudos:");
    display.print("áéíóúÁÉÍÓÚ");
    y += 18;
    
    // Acentos graves
    display.setCursor(0, y);
    display.println("Acentos Graves:");
    display.print("àèìòùÀÈÌÒÙ");
    y += 18;
    
    // Trema
    display.setCursor(0, y);
    display.println("Trema:");
    display.print("äëïöüÄËÏÖÜ");
    
    display.display();
}

/**
 * @brief Mostra símbolos de setas e formas
 */
void showArrowsAndShapes() {
    drawHeader("SETAS E FORMAS");
    
    int y = 12;
    display.setCursor(0, y);
    
    // Setas
    display.println("Setas:");
    display.print("←↑→↓↔↕");
    y += 18;
    
    // Formas geométricas
    display.setCursor(0, y);
    display.println("Formas:");
    display.print("■□▲▼◆◇○●");
    y += 18;
    
    // Símbolos técnicos
    display.setCursor(0, y);
    display.println("Tecnicos:");
    display.print("⌂⌐¬±µΩ");
    
    display.display();
}

/**
 * @brief Mostra página de teste de fonte
 */
void showFontTest() {
    drawHeader("TESTE DE FONTES");
    
    int y = 12;
    
    // Tamanho 1
    display.setTextSize(1);
    display.setCursor(0, y);
    display.println("Tamanho 1: ABCabc123");
    y += 10;
    
    // Tamanho 2
    display.setTextSize(2);
    display.setCursor(0, y);
    display.println("T2:ABC");
    y += 16;
    
    // Tamanho 3 (se couber)
    if(y + 24 <= 64) {
        display.setTextSize(3);
        display.setCursor(0, y);
        display.println("T3:AB");
    }
    
    // Volta ao tamanho normal
    display.setTextSize(1);
    
    display.display();
}

/**
 * @brief Setup inicial
 */
void setup() {
    Serial.begin(115200);
    Serial.println("Iniciando Teste de Simbolos OLED");
    
    // Inicialização do display
    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("Falha na inicialização do SSD1306"));
        for(;;);
    }
    
    // Configuração inicial do display
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    
    // Ativa suporte a caracteres especiais
    display.cp437(true); // Usa tabela de caracteres Code Page 437
    
    // Tela de boas-vindas
    display.setTextSize(2);
    display.setCursor(15, 20);
    display.println("SIMBOLOS");
    display.setTextSize(1);
    display.setCursor(25, 45);
    display.println("TESTE COMPLETO");
    display.display();
    
    delay(3000);
}

/**
 * @brief Loop principal
 */
void loop() {
    // Mostra página atual
    switch(currentPage) {
        case 0:
            showASCIIBasic();
            break;
        case 1:
            showASCIIExtended();
            break;
        case 2:
            showSpecialSymbols();
            break;
        case 3:
            showGraphicCharacters();
            break;
        case 4:
            showInternationalChars();
            break;
        case 5:
            showArrowsAndShapes();
            break;
        case 6:
            showFontTest();
            break;
    }
    
    // Rolagem automática a cada 5 segundos
    if(millis() - lastScrollTime > SCROLL_DELAY) {
        currentPage = (currentPage + 1) % TOTAL_PAGES;
        lastScrollTime = millis();
    }
    
    delay(100);
}