#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct node
{
	int num;
	struct node *nxt;
}
Node;
Node *insert(Node *head, int n);
Node *delete(Node *head, int n);
int length(Node *head);
int contains(Node *head, int n);
void print(Node *head);
void deleteList(Node *head);
int main(void)
{
	Node *head = NULL;
	char cmd;
	int num;

	do
	{
		fflush(stdout);
		scanf("%c %d", &cmd, &num);
		if ((tolower(cmd) != 'i') && (tolower(cmd) != 'd'))
		{
			break;
		}
		if (tolower(cmd) == 'i')
		{
			head = insert(head, num);
		}
		else
		{
			head = delete(head, num);
		}
		printf("%d : ", length(head));
		print(head);
		printf("\n");

	}

	while ((tolower(cmd) == 'i') || (tolower(cmd) == 'd'));
	{
		deleteList(head);
		return EXIT_SUCCESS;
	}

}

Node *insert(Node *head, int n)
{
	if (contains(head, n) == 1)
	{
		return head;
	}

	Node *node = (Node*)malloc(sizeof(Node));

	if (node != NULL)
	{
		node -> num = n;
		node -> nxt = NULL;

		if (head == NULL)
		{
			head = node;
		}
		else
		{
			Node *crnt = head;
			Node *prev = NULL;
			while (crnt != NULL)
			{
				if (crnt -> num > node -> num)
				{
					if (prev == NULL)
					{
						node -> nxt = head;
						head = node;
					}
					else
					{
						node -> nxt = crnt;
						prev -> nxt = node;

					}
					return head;
				}
				prev = crnt;
				crnt = crnt -> nxt;
			}
			prev -> nxt = node;
		}
	}
	return head;
}


Node *delete(Node *head, int n)
{
	if (head != NULL)
	{
		if (head -> num == n)
		{
			Node *tmp = head;
			head = head -> nxt;
			free(tmp);
		}
		else
		{
			Node *crnt = head;
			Node *prev = NULL;

			while (crnt != NULL)
			{
				if (crnt -> num == n)
				{
					prev -> nxt = crnt -> nxt;
					free(crnt);
					return head;

				}

				prev = crnt;
				crnt = crnt -> nxt;
			}
		}
	}
	return head;
}


int length(Node *head)
{
	int count = 0;
	Node *crnt = head;
	while (crnt != NULL)
	{
		count++;
		crnt = crnt -> nxt;
	}
	return count;
}

void print(Node *head)
{
	Node *tmp = head;
	while (tmp != NULL)
	{
		printf("%d ", tmp -> num);
		tmp = tmp -> nxt;
	}
}

int contains(Node *head, int n)
{
	Node *crnt = head;
	while (crnt != NULL)
	{
		if (crnt -> num == n)
		{
			return EXIT_FAILURE;

		}
		crnt = crnt -> nxt;
	}
	return EXIT_SUCCESS;
}

void deleteList(Node *head)
{
	Node *crnt;
	while(head != NULL)
	{
		crnt = head;
		head = head -> nxt;
		free(crnt);
	}
}












