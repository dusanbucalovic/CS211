#include <stdio.h>
#include <stdlib.h>

struct node
{
	int key;
	struct node *left, *right;

}

struct node *newNode(int item)
{
	struct node *temp = (struct node *)malloc(sizeof(struct node));
	temp -> key = item;
	temp -> left = temp -> right = NULL;
	return temp;
}

void inorder(struct node *root)
{
	if (root != NULL)
	{
		print("(");
		inorder(root -> left);
		printf("%d", root -> key);
		inorder(root -> right);
		printf(")");

	}
}

struct node* search(struct node* root, int key)
{
	if (root == NULL || root -> key == key)
	{
		return root;
	}
	if (root -> key < key)
	{
		return search(root -> right, key);
		return search(root -> left, key);
	}

}

struct node* insert(struct node* node, int key)
{
	if (node == NULL)
	{
		printf("inserted\n");
		return newNode(key);
	}
	if(key < node -> key)
	{
		node -> left = insert(node -> left, key);

	}
	else if (key > node -> key)
	{
		node -> right = insert(node -> right, key);
	}
	else
	{
		printf("duplicate\n");
	}
	return node;
}

struct node * minValueNode(struct node* node)
{
	struct node* current = node;
	while (current -> left != NULL)
	{
		current = current -> left;
	}
	return current;
}

struct node* deleteNode(struct node* root, int key)
{
	if (root == NULL)
	{
		return root;

	}
	if (key < root -> key)
	{
		root -> left = deleteNode(root -> left, key);

	}
	else if (key > root -> key)
	{
		root -> right = deleteNode(root -> right, key);

	}
	else
	{
		if (root -> left == NULL)
		{
			struct node *temp = root -> right;
			free(root);
			return temp;
		}
		else if (root -> right == NULL)
		{
			struct node *temp = root -> left;
			free(root);
			return temp;
		}
		struct node* temp = minValueNode(root -> right);
		root -> key = temp -> key;
		root -> right = deleteNode(root -> right, temp -> key);
	}
	return root;
}

int isvalid(char command)
{
	if (command == 'i' || command == 'd' || command == 's' || command == 'p')
	{
		return 1;
	}
	else{
		return 0;
	}

}


int main()
{
	char command;
	int n;
	struct node *root = NULL;
	do
	{
		scanf("%c", &command);
		if(command == 'i')
		{
			scanf("%d", &n);
			root = insert(root, n );
		}
		else if(command == 'd')
		{
			scanf("%d", &n);
			root = deleteNode(root, n);
		}
		else if (command == 's')
		{
			scanf("%d", &n);
			if (search(root, n))
			{
				printf("present\n");

			}
			else
			{
				printf("absent\n");
			}
		}
		else if (command == 'p');
		{
			inorder(root);
			printf("\n");
		}
		else
		{
			command = 'q';
			while ((getchar())!='\n');
		}
	}
	while(isvalid(command));
	return 0;
}










