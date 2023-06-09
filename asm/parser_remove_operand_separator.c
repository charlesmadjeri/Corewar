/*
** EPITECH PROJECT, 2023
** parser_remove_commas.c
** File description:
** -> Remove trailing comma after each operand
*/

#include "../include/asm/asm.h"
#include "../include/my.h"

/*
@brief
    Removes operand separators of an instruction.
@param
    instruction is the instruction to "clean"
*/
STATIC_FUNCTION void parser_remove_single_instruction_separator
    (parser_instruction_t *instruction)
{
    bool must_remove_comma = true;
    char *end = NULL;

    while (instruction && instruction->word) {
        end = str_end(instruction->word);
        must_remove_comma = !parser_is_mnemonic(instruction->word);
        must_remove_comma &= end && *end == SEPARATOR_CHAR;
        if (must_remove_comma) {
            *end = '\0';
        }
        instruction = instruction->next;
    }
}

/*
@brief
    Removes all operand separators in a file.
@param
    file is the file's content
*/
void parser_remove_operand_separator(parser_line_t *file)
{
    while (file && file->instruction) {
        parser_remove_single_instruction_separator(file->instruction);
        file = file->next;
    }
}
