/**
 * @file ButtonManager.cpp
 * @brief Implementação da classe ButtonManager
 * @details Contém a lógica de debounce e gerenciamento de estados dos botões
 */

#include "ButtonManager.hpp"

/**
 * @brief Construtor da classe ButtonManager
 * @param debounce Tempo de debounce em milissegundos
 */
ButtonManager::ButtonManager(unsigned long debounce) 
    : debounceTime(debounce) {
    lastDebounce = millis();
    initializeButtons();
}

/**
 * @brief Inicializa todos os botões com configurações padrão
 * @details Configura pinos como INPUT_PULLUP e inicializa estruturas
 */
void ButtonManager::initializeButtons() {
    // Configurar botões conforme definição fixa
    uint8_t pins[TOTAL_BUTTONS] = {PINO_MENU, PINO_ESC, PINO_UP, PINO_DOWN, PINO_RIGHT, PINO_LEFT};
    
    for(uint8_t i = 0; i < TOTAL_BUTTONS; i++) {
        buttons[i].pin = pins[i];
        buttons[i].pressed = false;
        buttons[i].previousState = false;
        buttons[i].pressCount = 0;
        buttons[i].name = BUTTON_NAMES[i];
        
        // Configurar pino como entrada com resistor pull-up interno
        pinMode(pins[i], INPUT_PULLUP);
    }
}

/**
 * @brief Atualiza o estado de todos os botões
 * @details Aplica debounce e detecta transições de estado
 */
void ButtonManager::update() {
    // Verifica se passou tempo suficiente para debounce
    if(millis() - lastDebounce > debounceTime) {
        lastDebounce = millis();
        
        // Processa cada botão individualmente
        for(uint8_t i = 0; i < TOTAL_BUTTONS; i++) {
            // Lê estado atual (LOW = pressionado devido ao INPUT_PULLUP)
            bool currentState = (digitalRead(buttons[i].pin) == LOW);
            
            // Detecta borda de subida (botão pressionado)
            if(currentState && !buttons[i].previousState) {
                buttons[i].pressCount++;
                Serial.print("BOTAO ");
                Serial.print(buttons[i].name);
                Serial.println(" PRESSIONADO");
            }
            
            // Atualiza estados
            buttons[i].pressed = currentState;
            buttons[i].previousState = currentState;
        }
    }
}

/**
 * @brief Verifica se um botão está pressionado no momento
 * @param pin Número do pino a verificar
 * @return true se pressionado, false caso contrário
 */
bool ButtonManager::isPressed(uint8_t pin) const {
    for(uint8_t i = 0; i < TOTAL_BUTTONS; i++) {
        if(buttons[i].pin == pin) {
            return buttons[i].pressed;
        }
    }
    return false;
}

/**
 * @brief Verifica se um botão estava pressionado na última verificação
 * @param pin Número do pino a verificar
 * @return true se estava pressionado, false caso contrário
 */
bool ButtonManager::wasPressed(uint8_t pin) const {
    for(uint8_t i = 0; i < TOTAL_BUTTONS; i++) {
        if(buttons[i].pin == pin) {
            return buttons[i].previousState;
        }
    }
    return false;
}

/**
 * @brief Obtém contagem de pressionamentos de um botão
 * @param pin Número do pino a verificar
 * @return Número de vezes que o botão foi pressionado
 */
unsigned long ButtonManager::getPressCount(uint8_t pin) const {
    for(uint8_t i = 0; i < TOTAL_BUTTONS; i++) {
        if(buttons[i].pin == pin) {
            return buttons[i].pressCount;
        }
    }
    return 0;
}

/**
 * @brief Calcula o total de pressionamentos de todos os botões
 * @return Soma de todos os contadores individuais
 */
unsigned long ButtonManager::getTotalPressCount() const {
    unsigned long total = 0;
    for(uint8_t i = 0; i < TOTAL_BUTTONS; i++) {
        total += buttons[i].pressCount;
    }
    return total;
}

/**
 * @brief Obtém nome amigável de um botão
 * @param pin Número do pino a verificar
 * @return Nome do botão ou "UNKNOWN" se não encontrado
 */
const char* ButtonManager::getButtonName(uint8_t pin) const {
    for(uint8_t i = 0; i < TOTAL_BUTTONS; i++) {
        if(buttons[i].pin == pin) {
            return buttons[i].name;
        }
    }
    return "UNKNOWN";
}

/**
 * @brief Retorna quantidade de botões gerenciados
 * @return Número total de botões configurados
 */
uint8_t ButtonManager::getButtonCount() const {
    return TOTAL_BUTTONS;
}

/**
 * @brief Obtém pino por índice
 * @param index Índice do botão (0 a TOTAL_BUTTONS-1)
 * @return Número do pino ou 0 se índice inválido
 */
uint8_t ButtonManager::getButtonPin(uint8_t index) const {
    if(index < TOTAL_BUTTONS) {
        return buttons[index].pin;
    }
    return 0;
}

/**
 * @brief Zera todos os contadores de pressionamento
 */
void ButtonManager::resetCounters() {
    for(uint8_t i = 0; i < TOTAL_BUTTONS; i++) {
        buttons[i].pressCount = 0;
    }
}