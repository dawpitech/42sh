/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** prompt header
*/

#include <malloc.h>
#include <stddef.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>

#include "minishell.h"
#include "ansi_chars.h"

static
bool is_git_repo(void)
{
    FILE *fp;
    char tmp[1024];
    bool rt_value = false;

    fp = popen("git rev-parse --is-inside-work-tree 2>/dev/null", "r");
    if (fp == NULL)
        return false;
    if (fgets(tmp, 1024, fp) == NULL) {
        pclose(fp);
        return false;
    }
    if (strncmp(tmp, "true", 4) == 0)
        rt_value = true;
    pclose(fp);
    return rt_value;
}

static
char *get_git_branch(void)
{
    FILE *fp;
    char *branch_name = calloc(1024, sizeof(char));

    fp = popen("git rev-parse --abbrev-ref HEAD", "r");
    if (fp == NULL)
        return NULL;
    if (fgets(branch_name, 1024 - 1, fp) == NULL) {
        pclose(fp);
        return NULL;
    }
    pclose(fp);
    branch_name[strlen(branch_name) - 1] = '\0';
    return branch_name;
}

static
char *get_current_dir(void)
{
    char *current_dir = calloc(1024, sizeof(char));
    char *cd_cpy = current_dir;
    char *cwd = getcwd(current_dir, 1024);

    if (cwd == NULL)
        return NULL;
    if (strcmp(cwd, "/") != 0) {
        current_dir = strdup(strrchr(current_dir, '/') + 1);
        free(cd_cpy);
    }
    return current_dir;
}

static
void print_prompt(shell_t *shell)
{
    char *color = shell->last_exit_code != 0 ? AC_C_RED : AC_C_GREEN;
    char *branch_name;
    char *current_dir = get_current_dir();

    if (!shell->isatty)
        return;
    printf("%s%s➜ %s%s%s ", AC_BOLD, color, AC_C_BRIGHT_BLUE, current_dir,
            AC_RESET);
    if (is_git_repo()) {
        branch_name = get_git_branch();
        printf("on %s%s%s %s %s", AC_C_MAGENTA, AC_BOLD, "", branch_name,
                AC_RESET);
        free(branch_name);
    }
    printf("❯ ");
    free(current_dir);
    fflush(stdout);
}

static
struct termios init_termios(void)
{
    struct termios old_config;
    struct termios new_config;

    tcgetattr(STDIN_FILENO, &old_config);
    new_config = old_config;
    new_config.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_config);
    return old_config;
}

static
void remove_char(shell_t *shell)
{
    if (shell->prompt->cursor_pos <= 0)
        return;
    if (strlen(shell->prompt->input) > 0) {
        memmove(&shell->prompt->input[shell->prompt->cursor_pos - 1],
                &shell->prompt->input[shell->prompt->cursor_pos],
                strlen(shell->prompt->input) - shell->prompt->cursor_pos + 1);
        write(STDOUT_FILENO, "\033[2K", 4);
        write(STDOUT_FILENO, "\r", 1);
        print_prompt(shell);
        write(STDOUT_FILENO, shell->prompt->input, shell->prompt->len);
        for (int i = 0; i <
                (int) shell->prompt->len - shell->prompt->cursor_pos; i += 1)
            write(STDOUT_FILENO, "\033[D", 3);
        shell->prompt->cursor_pos -= 1;
        shell->prompt->cursor_pos = shell->prompt->cursor_pos;
        shell->prompt->len -= 1;
    }
}

static
void add_char(shell_t *shell)
{
    shell->prompt->input = realloc(shell->prompt->input,
            shell->prompt->len + 2);
    memmove(&shell->prompt->input[shell->prompt->cursor_pos + 1],
            &shell->prompt->input[shell->prompt->cursor_pos],
            shell->prompt->len - shell->prompt->cursor_pos);
    shell->prompt->input[shell->prompt->cursor_pos] = shell->prompt->ch;
    shell->prompt->len += 1;
    shell->prompt->cursor_pos += 1;
    write(STDOUT_FILENO, "\033[2K", 4);
    write(STDOUT_FILENO, "\r", 1);
    print_prompt(shell);
    write(STDOUT_FILENO, shell->prompt->input, shell->prompt->len);
    for (int i = 0;
            i < (int) shell->prompt->len - shell->prompt->cursor_pos; i += 1)
        write(STDOUT_FILENO, "\033[D", 3);
}

static
void handle_arrow_keys(shell_t *shell)
{
    (void)!getchar();
    shell->prompt->ch = (char)getchar();
    switch (shell->prompt->ch) {
        case 'D':
            if (shell->prompt->cursor_pos <= 0)
                break;
            write(STDOUT_FILENO, "\033[D", 3);
            shell->prompt->cursor_pos -= 1;
            break;
        case 'C':
            if (shell->prompt->cursor_pos >= (int)strlen(shell->prompt->input))
                break;
            write(STDOUT_FILENO, "\033[C", 3);
            shell->prompt->cursor_pos += 1;
            break;
        default:
            break;
    }
}

static
char *get_from_stdin(shell_t *shell)
{
    struct termios old_config = init_termios();

    do {
        shell->prompt->ch = (char) getchar();
        if (shell->prompt->ch == '\n' || shell->prompt->ch == 4)
            break;
        if (shell->prompt->ch == 127) {
            remove_char(shell);
            continue;
        }
        if (shell->prompt->ch == 27) {
            handle_arrow_keys(shell);
            continue;
        }
        add_char(shell);
    } while (1);
    tcsetattr(STDIN_FILENO, TCSANOW, &old_config);
    printf("\n");
    return shell->prompt->input;
}

int present_prompt(shell_t *shell)
{
    shell->cmds_valid = true;
    shell->prompt = malloc(sizeof(prompt_t));
    shell->prompt->input = calloc(1, sizeof(char));
    shell->prompt->cursor_pos = 0;
    shell->prompt->len = 0;
    shell->prompt->ch = 0;
    if (shell->prompt == NULL)
        return RET_ERROR;
    print_prompt(shell);
    shell->prompt->raw_input = get_from_stdin(shell);
    if (shell->prompt->raw_input != NULL)
        return RET_VALID;
    shell->running = false;
    free(shell->prompt);
    return RET_ERROR;
}
