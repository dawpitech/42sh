/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** display_parse header
*/

static
void display_parser(root_t *root)
{
    for (int i = 0; root->tab_sc[i] != NULL; i ++) {
        printf("tab_sc[%d]\n", i);
        for (int j = 0; root->tab_sc[i]->tab_and[j] != NULL; j ++) {
            printf("\ttab_and[%d]\n", j);
            for (int k = 0; root->tab_sc[i]->tab_and[j]->tab_or[k] != NULL; k ++) {
                printf("\t\ttab_or[%d]\n", k);
                for (int l = 0; root->tab_sc[i]->tab_and[j]->tab_or[k]->tab_pipe[l] != NULL; l ++) {
                    printf("\t\t\ttab_pipe[%d]\n", l);
                    for (int m = 0; root->tab_sc[i]->tab_and[j]->tab_or[k]->tab_pipe[l]->tab_command[m] != NULL; m ++) {
                        printf("\t\t\t\ttab_command[%d]\n", m);
                        printf("\t\t\t\t\tstring : %s args : ", root->tab_sc[i]->tab_and[j]->tab_or[k]->tab_pipe[l]->tab_command[m]->argv[0]);
                        for (int n = 0; root->tab_sc[i]->tab_and[j]->tab_or[k]->tab_pipe[l]->tab_command[m]->argv[n] != NULL; n ++)
                            printf("%s ", root->tab_sc[i]->tab_and[j]->tab_or[k]->tab_pipe[l]->tab_command[m]->argv[n]);
                        printf("\n");
                    }
                }
            }
        }
    }
}
