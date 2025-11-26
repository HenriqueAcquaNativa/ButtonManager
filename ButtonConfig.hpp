/**
 * @file ButtonConfig.hpp
 * @brief Configuração dos pinos e nomes dos botões
 * @details Define os pinos fixos e nomes para todos os botões do sistema
 */

#ifndef BUTTON_CONFIG_HPP
#define BUTTON_CONFIG_HPP

// Definição FIXA dos pinos dos botões
#define PINO_MENU    3    /**< Pino digital para o botão MENU */
#define PINO_ESC     2    /**< Pino digital para o botão ESC */
#define PINO_UP      5    /**< Pino digital para o botão UP */
#define PINO_DOWN    13   /**< Pino digital para o botão DOWN */
#define PINO_RIGHT   11   /**< Pino digital para o botão RIGHT */
#define PINO_LEFT    12   /**< Pino digital para o botão LEFT */

/**
 * @brief Nomes dos botões para debug e display
 * @note A ordem deve corresponder à ordem dos pinos acima
 */
const char* const BUTTON_NAMES[] = {
    "MENU", "ESC", "UP", "DOWN", "RIGHT", "LEFT"
};

/**
 * @brief Número total de botões no sistema
 */
const uint8_t TOTAL_BUTTONS = 6;

#endif