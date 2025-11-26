/**
 * @file ButtonManager.hpp
 * @brief Gerenciador de botões com debounce
 * @details Classe para gerenciar múltiplos botões com contagem de pressionamentos
 */

#ifndef BUTTON_MANAGER_HPP
#define BUTTON_MANAGER_HPP

#include <Arduino.h>
#include "ButtonConfig.hpp"

/**
 * @class ButtonManager
 * @brief Gerencia o estado e contagem de múltiplos botões
 */
class ButtonManager {
private:
    /**
     * @struct Button
     * @brief Estrutura que representa um botão individual
     */
    struct Button {
        uint8_t pin;                    /**< Pino digital do botão */
        bool pressed;                   /**< Estado atual (pressionado/liberado) */
        bool previousState;             /**< Estado anterior para detecção de borda */
        unsigned long pressCount;       /**< Contador de pressionamentos */
        const char* name;               /**< Nome do botão para display */
    };

    Button buttons[TOTAL_BUTTONS];      /**< Array de botões gerenciados */
    unsigned long lastDebounce;         /**< Último tempo de debounce */
    const unsigned long debounceTime;   /**< Tempo de debounce em milissegundos */

    /**
     * @brief Inicializa todos os botões com configurações padrão
     */
    void initializeButtons();

public:
    /**
     * @brief Construtor da classe ButtonManager
     * @param debounce Tempo de debounce em ms (padrão: 50ms)
     */
    ButtonManager(unsigned long debounce = 50);
    
    /**
     * @brief Atualiza o estado de todos os botões
     * @details Verifica o estado atual e aplica debounce
     */
    void update();
    
    /**
     * @brief Verifica se um botão está pressionado no momento
     * @param pin Número do pino a verificar
     * @return true se o botão está pressionado, false caso contrário
     */
    bool isPressed(uint8_t pin) const;
    
    /**
     * @brief Verifica se um botão estava pressionado na última verificação
     * @param pin Número do pino a verificar
     * @return true se o botão estava pressionado, false caso contrário
     */
    bool wasPressed(uint8_t pin) const;
    
    /**
     * @brief Obtém o número de vezes que um botão foi pressionado
     * @param pin Número do pino a verificar
     * @return Contador de pressionamentos do botão
     */
    unsigned long getPressCount(uint8_t pin) const;
    
    /**
     * @brief Obtém o total de pressionamentos de todos os botões
     * @return Soma de todos os pressionamentos
     */
    unsigned long getTotalPressCount() const;
    
    /**
     * @brief Obtém o nome de um botão baseado no pino
     * @param pin Número do pino a verificar
     * @return Nome do botão ou "UNKNOWN" se não encontrado
     */
    const char* getButtonName(uint8_t pin) const;
    
    /**
     * @brief Obtém o número total de botões gerenciados
     * @return Quantidade de botões configurados
     */
    uint8_t getButtonCount() const;
    
    /**
     * @brief Obtém o pino de um botão pelo índice
     * @param index Índice do botão (0 a TOTAL_BUTTONS-1)
     * @return Número do pino ou 0 se índice inválido
     */
    uint8_t getButtonPin(uint8_t index) const;
    
    /**
     * @brief Zera todos os contadores de pressionamento
     */
    void resetCounters();
};

#endif