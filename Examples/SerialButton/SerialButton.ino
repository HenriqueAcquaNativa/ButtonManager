/**
 * @file ButtonTest.ino
 * @brief Teste da biblioteca ButtonManager
 * @details Imprime na serial qual botão foi pressionado
 */

#include "ButtonManager.hpp"

// Cria instância do gerenciador de botões com debounce de 50ms
ButtonManager buttonManager(50);

void setup() {
  // Inicializa comunicação serial
  Serial.begin(9600);
  Serial.println("=== SISTEMA DE TESTE DE BOTOES ===");
  Serial.println("Pressione qualquer botao para testar");
  Serial.println("===================================");
  
  // Aguarda inicialização estável
  delay(1000);
}

void loop() {
  // Atualiza o estado de todos os botões
  buttonManager.update();
  
  // Verifica cada botão individualmente
  for(uint8_t i = 0; i < buttonManager.getButtonCount(); i++) {
    uint8_t pin = buttonManager.getButtonPin(i);
    
    // Se o botão está pressionado agora mas não estava antes
    if(buttonManager.isPressed(pin) && !buttonManager.wasPressed(pin)) {
      printButtonInfo(pin);
    }
  }
  
  // Pequeno delay para evitar sobrecarga
  delay(10);
}

/**
 * @brief Imprime informações do botão pressionado
 * @param pin Número do pino do botão pressionado
 */
void printButtonInfo(uint8_t pin) {
  const char* nome = buttonManager.getButtonName(pin);
  unsigned long contador = buttonManager.getPressCount(pin);
  unsigned long total = buttonManager.getTotalPressCount();
  
  Serial.println("-----------------------------------");
  Serial.print("BOTAO PRESSIONADO: ");
  Serial.println(nome);
  Serial.print("Pino: ");
  Serial.println(pin);
  Serial.print("Vezes pressionado: ");
  Serial.println(contador);
  Serial.print("Total de pressionamentos (todos botoes): ");
  Serial.println(total);
  Serial.println("-----------------------------------");
  Serial.println(); // Linha em branco para separar
}

/*

=== SISTEMA DE TESTE DE BOTOES ===
Pressione qualquer botao para testar
===================================
-----------------------------------
BOTAO PRESSIONADO: MENU
Pino: 3
Vezes pressionado: 1
Total de pressionamentos (todos botoes): 1
-----------------------------------

-----------------------------------
BOTAO PRESSIONADO: UP
Pino: 5
Vezes pressionado: 1
Total de pressionamentos (todos botoes): 2
-----------------------------------
*/