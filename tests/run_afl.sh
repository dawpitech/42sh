afl-fuzz \
  -o tests/generated           \
  -m none                      \
  -i tests/inputs/commands     \
  -x tests/inputs/tokens       \
  -- ./minishell
