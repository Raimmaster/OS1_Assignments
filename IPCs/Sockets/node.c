#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct process_node {
  int value;
  long left_son;
  long right_son;
} node_t;

int show_menu_get_answer()
{
    printf("1. Crear proceso.\n2. Buscar proceso.\n3. Borrar proceso.\n");
    int answer;
    scanf("%d\n", &answer);

    return answer;
}

void create_node(node_t* node, int val)
{
  if(node == NULL)
  {
    pid_t pid = fork();
    if(pid == 0)
    {
      node = malloc(sizeof(node_t));
      (*node).value = val;
    }
  }else
  {
    if(val < (*node).value)
    {
      create_node((*node).left_son, val);
    }else if (val > (*node).value)
    {
      create_node((*node).right_son, val);
    }
  }
}

int search_node(node_t* node, int val)
{
  if(node == NULL)
  {
    return -1;
  }

  if((*node).value == val)
  {
    printf("Found! My pid is %d and my parent is %d\n", getpid(), getppid());
    return 1;
  }

  if(val > (*node).value)
  {
    return search_node((*node).right_son, val);
  }

  if(val < (*node).value))
  {
    return search_node((*node).left_son, val);
  }
}

void kill(node_t* node, int val)
{
  if(node == NULL)
    return;

  if((*node).value == val)
  {

  }
}

int main(int argc, char const *argv[]) {
  switch (show_menu_get_answer) {
    case 1:

      break;
    case 2:
      break;
    case 3:
      break;
    default:
      break;
  }

  return 0;
}
