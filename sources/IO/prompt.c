/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** prompt header
*/

#include <malloc.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>

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
    fgets(tmp, 1024, fp);
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
    fgets(branch_name, 1024 - 1, fp);
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
}

static
char *get_from_stdin(void)
{
    char *line = NULL;
    size_t buff_value = 0;
    int rt_value;

    rt_value = (int) getline(&line, &buff_value, stdin);
    if (rt_value <= 0) {
        printf("exit\n");
        free(line);
        return NULL;
    }
    line[strlen(line) - 1] = '\0';
    return line;
}

int present_prompt(shell_t *shell)
{
    shell->cmds_valid = true;
    shell->prompt = malloc(sizeof(prompt_t));
    if (shell->prompt == NULL)
        return RET_ERROR;
    print_prompt(shell);
    shell->prompt->raw_input = get_from_stdin();
    if (shell->prompt->raw_input != NULL)
        return RET_VALID;
    shell->running = false;
    free(shell->prompt);
    return RET_ERROR;
}
