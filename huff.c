#include <stdio.h>
#include <stdlib.h>
 
// This constant can be height of Huffman Tree (max predicted height)
#define MAX_TREE_HT 256
 
// A Huffman Tree node
struct node
{
    char data;  // One of the input characters
    int freq;  // Frequency of the character
    struct node *left, *right; // Left and right child of this node
};
 
// A Heap Data Structure:  Collection of heap (or Hufmman tree) nodes
struct heap
{
    int size;    // Current size of min heap
    int capacity;   // capacity of min heap
    struct node **array;  // Array of heap node pointers, points to the character as well as its's frequency 
};

struct node* buildHuffmanTree(char d[], int f[], int );
struct heap* createAndBuildheap(char d[], int f[], int );
struct heap* createheap(int );
struct node* newNode(char , int );
void buildheap(struct heap* );
void heapify(struct heap* , int );
void swapnode(struct node** , struct node** );
void insertheap(struct heap* , struct node* );
void printCodes(struct node* , int a[], int );
int isSizeOne(struct heap* );
struct node* extractMin(struct heap* );
int isLeaf(struct node* );
void printArr(struct node* , int a[], int );

int main()
{   
	char arr[256];	//array to store the characters of the file
	int freq[256];	//array to store the frequency of respective character in the file
	
	int count[256] = { 0 };  //array to count the frequency of each character initially assinging the value 0
	
	int i,j,s=0,y=0,z=0,choice;
	char c;
		
	FILE *fp = fopen("C://Users/Abhishek/Desktop/new.txt", "r");
	
	if(fp == NULL)
	{
		printf("Coudn't able to open the file \n");
	}
	
	else
	{
		while((c = fgetc(fp)))
		{
			if(c == EOF)
				break;
			else
				count[c] = count[c] + 1; //Counting the frequency of each character
		}
	}
	  
	for(i=0; i<256; i++)
	{
		if(count[i] > 0)
		{
			arr[z] = i;	//Copying the character element to the array if the freq. is greater then zero
			z=z+1;
		}
	}
	
	for(i=0;i<256;i++)
	{
		if(count[i]>0)
		{
			freq[y]=count[i];	//Copying the frequency of the character to it's same location i of arr[i]
			y++;
		}
	}
	
	for(i=0;i<256;i++)
	{
		if(count[i]>0)
		{
			s = s+1;	//Counting the number of characters in our file
		}
	}

	printf("Our Input Is: \n");
	printf("\nThe No. of the Characters: %d\n\n", s);
	
	printf("\tCHARACTER\tFREQUENCY\n\n");
	
	for(i=0; i<s; i++)
	{
		printf("\t%c\t\t%d\n", arr[i], freq[i]);
	}
	
	loop:
	printf("\n\tPress [1] for Huffman Code Data Compression.\n");
	printf("\tPress [2] for Ziv-Lempel Code Text Compression.\n");
	printf("\tPress [3] for Exit.\n");
	printf("\tEnter your Choice : ");
	scanf("%d", &choice);
	
	switch(choice)
	{
		while(1)
		{
			case 1:
				printf("\nThe Resulting Codes from the HUFFMAN Tree are:\n\n");
				printf("\nCHARACTER   FREQUENCY   BINARY-CODES\tCODE-LENGTH   MEMORY (Bits)\n\n");
				HuffmanCodes(arr, freq, s);
				goto loop;
				break;
			
			case 2:
				printf("\n\tCode for Ziv Lemepel Algorithm Code not Present\n");
				goto loop;
				break;
				
			case 3:
				printf("\n\tExiting...\n");
				exit(1);
				
			default:
				printf("\n\tYou have chosen a wrong input.\n");
				printf("\n\tPlease try again...\n");
				goto loop;
				break;
		}
	}				
	
	fclose(fp);
	
	return 0;
}

// HuffmanCodes function builds a Huffman Tree and print codes by traversing the built Huffman Tree
int HuffmanCodes(char data[], int freq[], int size)
{
   	struct node* root;
   	int arr[MAX_TREE_HT], top = 0;
   
	root = buildHuffmanTree(data, freq, size);	//  Construct Huffman Tree
   
	printCodes(root, arr, top);	// Print Huffman codes using the Huffman tree built above
}

// The main function that implements the Huffman Algorithm to build the Huffman Tree
struct node* buildHuffmanTree(char data[], int freq[], int size)
{
    struct node *left, *right, *top;
 
    //Step 1: Create a heap of given capacity.
    struct heap* heap;
	heap = createAndBuildheap(data, freq, size);
 
    //We will follow the steps 2 and 3 if and only if the Heap does not contain only a single node.
    while (!isSizeOne(heap))
    {
        // Step 2: Extract the two minimum freq items from Heap
        
        //This comes out to be the left node of the huffman tree having the least possible frequency
		left = extractMin(heap);
		
		//This comes out to be the Right node of the huffman tree having the frequency just greater than the left node
        right = extractMin(heap);	
 
        /* Step 3:  Create a new internal node with frequency equal to the
         			sum of the two nodes frequencies. Make the two extracted node as
         			left and right children of this new node. Add this node to the min heap
         			'$' is a special value for internal nodes, which is not used
		*/
        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        
		insertheap(heap, top);	//this inserts the new node (root node) to the heap
    }
 
    // Step 4: The remaining node is the root node and the tree is complete.
    return extractMin(heap);
}

// Function to create a Heap of given capacity (size) and insert all the given characters
struct heap* createAndBuildheap(char data[], int freq[], int size)
{
    int i;
	struct heap* heap = createheap(size);
    for (i = 0; i < size; ++i)
        heap->array[i] = newNode(data[i], freq[i]);
    heap->size = size;
    buildheap(heap);
    return heap;
}

// createheap function to create a Heap of given capacity
struct heap* createheap(int capacity)
{
    struct heap* heap = (struct heap* ) malloc(sizeof(struct heap));
    heap->size = 0;  // current size is 0
    heap->capacity = capacity;
    heap->array = (struct node **)malloc(heap->capacity * sizeof(struct node*));
    return heap;
}


// newNode function allocatse a new Heap node with given character and frequency of that character
struct node* newNode(char data, int freq)
{
    struct node* temp = (struct node *) malloc(sizeof(struct node));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}

// buildheap function builds the Heap of the given size
// while traversing the heap in a Min Heap Manner
void buildheap(struct heap* heap)
{
    int n = heap->size - 1;
    int i;
    for (i = (n - 1) / 2; i >= 0; --i)
        heapify(heap, i);
}

// Heapify function : used to design the actual Huffman Tree
// calculating the minimum left and right tree nodes first
// while traversing through the given array
// Then joining them to their parent node
// Parent node is the sum of the indivisual frequencies of the two leaf nodes.
void heapify(struct heap* heap, int idx)
{
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
 
    if (left < heap->size && heap->array[left]->freq < heap->array[smallest]->freq)
      smallest = left;
 
    if (right < heap->size && heap->array[right]->freq < heap->array[smallest]->freq)
      smallest = right;
 
    if (smallest != idx)
    {
        swapnode(&heap->array[smallest], &heap->array[idx]);
        heapify(heap, smallest);
    }
}

// swapnode function swaps two given Heap nodes according to their frequencies
void swapnode(struct node** a, struct node** b)
{
    struct node* t = *a;
    *a = *b;
    *b = t;
}

// insertheap function to insert a new node to Heap
void insertheap(struct heap* heap, struct node* node)
{
    int i;
	++heap->size;	//increment the heap memory by one each time a new node is inserted to heap
    i = heap->size - 1;	//Size of the given array is decremented, once the value is pulled out to be compared.
    
	while (i && node->freq < heap->array[(i - 1)/2]->freq) //i is a memory and we need to check where the subtree is to be placed inside the heap
    {
        heap->array[i] = heap->array[(i - 1)/2];   // Assign the array value to the heap unless it becomes the greater
        i = (i - 1)/2;	
    }
    heap->array[i] = node;	// Heap now contains the new node at ith memory location
}

// Prints huffman codes from the root of Huffman Tree.  It uses arr[] to store codes.
void printCodes(struct node* root, int arr[], int top)
{
	// Assign 0 to left edge and recur
	if (root->left)
    {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }
 
    // Assign 1 to right edge and recur
    if (root->right)
    {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }
 
    // If this is a leaf node, then it prints the character and its code from arr[]
    if (isLeaf(root))
    {
        printf("    %c\t\t%d\t", root->data, root->freq);
        printArr(root, arr, top);
    }
}

// isSizeOne function is used to check if the size of Heap is 1 or not
int isSizeOne(struct heap* heap)
{
    return (heap->size == 1);
}
 
// extractMin function extracts the minimum value node from Heap
struct node* extractMin(struct heap* heap)
{
    struct node* temp = heap->array[0];
    heap->array[0] = heap->array[heap->size - 1]; //size of the array[] is decremented by one
    --heap->size;	//heap size reduced
    heapify(heap, 0);
    return temp;
}

// isLeaf checks if this node is leaf or not
int isLeaf(struct node* root)
{
    return !(root->left) && !(root->right);
}

// printArr function prints the Huffman Tree codes
void printArr(struct node *root, int arr[], int n)
{
    int i,c;
    
    for (i = 0; i < n; ++i)
    {
        printf("%d", arr[i]);
    }
	
	if(n < 8)
	{
		printf("\t\t%d\t", n);
		c = root->freq;
		printf("\t%d", c*n);
		printf("\n");
	}
	
	else
	if(n >=8)
	{
		printf("\t%d\t", n);
		c = root->freq;
		printf("\t%d", c*n);
		printf("\n");
	}
}
