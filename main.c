/**************************************************************************************************************************************************************
*Title		: main function(Driver function)
*Description	: This function is used as the driver function for the all the functions
***************************************************************************************************************************************************************/
#include "rbt.h"

int main()
{
	/* Declare the pointers */
	data_t operation;
	char option;
	tree_t *root = NULL;
	data_t data;
	data_t minimum;
	data_t maximum;

	do
	{
		/* Display the menu */
		printf("1. Insert\n2. Delete\n3. Find Minimum\n4. Delete Minimum\n5. Find Maximum\n6. Delete Maximum\n");
		printf("Enter your choice: ");
		scanf("%d", &operation);
		/* Read the option for performing the operation */

		/* Jump to the option entered by the user */
		switch (operation)
		{
			case 1:
				printf("Enter the data to be inserted into the RB Tree: ");
				scanf("%d", &data);
				if(insert(&root, data) == SUCCESS)
				{
					printf("Data %d inserted successfully.\n", data);
				}
				else
				{
					printf("ERROR : Insertion failed for data, may be duplicate data %d.\n", data);
				}
				/* Modify the above line to handle the error */
				print_tree(root);
				printf("\n");
				break;
			case 2:
				if(root == NULL){
					printf("Tree is empty.\n");
					break;
				}
				printf("Enter the data to be deleted from the RB Tree: ");
				scanf("%d", &data);
				if(delete(&root, data) == SUCCESS)
				{
					printf("Data %d deleted successfully.\n", data);
				}
				else
				{
					printf("Data %d not found in the tree.\n", data);
				}
				/* Modify the above line to handle the error */
				print_tree(root);
				printf("\n");
				break;
			case 3:
				// find_minimum(&root);
				/* Modify the above line to handle the error */
				if(root == NULL){
					printf("Tree is empty.\n");
					break;
				}
				printf("Minimum data: %d\n", find_minimum(root)->data);
				print_tree(root);
				printf("\n");
				break;
			case 4:
				if(root == NULL){
					printf("Tree is empty.\n");
					break;
				}
				if(delete_minimum(&root) == SUCCESS)
				{
					printf("Minimum data deleted successfully.\n");
				}
				else
				{
					printf("ERROR : Deletion of minimum data failed.\n");
				}
				/* Modify the above line to handle the error */
				print_tree(root);
				printf("\n");
				break;
			case 5:
				
				/* Modify the above line to handle the error */
				if(root == NULL){
					printf("Tree is empty.\n");
					break;
				}
				printf("Maximum data: %d\n", find_maximum(root)->data);
				print_tree(root);
				printf("\n");
				break;				
			case 6:
				if(root == NULL){
					printf("Tree is empty.\n");
					break;
				}
				if(delete_maximum(&root) == SUCCESS)
				{
					printf("Maximum data deleted successfully.\n");
				}
				else
				{
					printf("ERROR : Deletion of maximum data failed.\n");
				}
				/* Modify the above line to handle the error */
				print_tree(root);
				printf("\n");
				break;				
		}
		printf("Want to continue? Press [yY | nN]: ");
		scanf("\n%c", &option);
	}while (option == 'y' || option == 'Y');

	return 0;
}
