#include <stdio.h>
#include <string.h>

void first_fit(int p_size[], int n, int blockSize[], int m);
void memoryAllotedTable(int p_size[], int allocation[], int n);
void block_displaying(int allocation[], int m);
int wastedBlocks(int allocation[], int m);
int memorySizeUsed(int p_size[], int n);
void memoryLeft(int blockSize[], int m);
float fragmentation(int blockSize[], int m, int destArray[]);
float avg_fragmentatioon(int total_fragmentation, int n);
int allocation[100]; // i set default allocation size as 100

// main function
int main()
{

    printf("First-Fit Memory Management Algorithm");
    int n, m; // intializing n and m
    printf("\nEnter the number of processes: ");
    scanf("%d", &n); // Taking user input for no.of processes user want to add
    int p_size[n];   // intitalizing p_size array with length n

    // Taking user input of process sizes with n iterations
    for (int i = 0; i < n; i++)
    {
        printf("Enter the size of process %d: ", i + 1);
        scanf("%d", &p_size[i]);
    }

    printf("\n\nEnter the number of blocks: ");
    scanf("%d", &m);  // Taking input for no.of blocks user want to add
    int blockSize[m]; // intitalizing blockSize array with length m

    // Taking user input of block sizes with m iterations
    for (int i = 0; i < m; i++)
    {
        printf("Enter the size of block %d: ", i + 1);
        scanf("%d", &blockSize[i]);
    }

    int destArray[m]; // a temperary array for storing intial block sizes

    // adding elements of block size array to destArray by iterating each element
    for (int i = 0; i < m; i++)
    {
        destArray[i] = blockSize[i];
    }

    printf("\n\n\n**Memory Management Algorithm**");

    // It takes three arguments - a pointer to the starting address of the memory to be filled, the value to be set,
    // and the number of bytes to be filled with the value
    memset(allocation, -1, sizeof(allocation)); // Initialize allocation array to -1

    first_fit(p_size, n, blockSize, m); // Run First Fit algorithm

    memoryAllotedTable(p_size, allocation, n); // display allocation table

    block_displaying(allocation, m); // Display number of allocated blocks

    int wasted_blocks = wastedBlocks(allocation, m); // Calculate wasted blocks
    printf("Number of wasted blocks: %d\n", wasted_blocks);

    int allocated_memory = memorySizeUsed(p_size, n); // return total memory  allocated to blocks
    printf("Allocated memory: %d\n", allocated_memory);

    memoryLeft(blockSize, m); // display remaining memory after allocation of the processes

    float total_fragmentation = fragmentation(blockSize, m, destArray); // calculate fragmentation
    printf("Total Fragmentation: %.2f\n", total_fragmentation);

    float avg_fragmentation = avg_fragmentatioon(total_fragmentation, n); // Calculate average fragmentation
    printf("Average fragmentation: %.2f\n", avg_fragmentation);

    return 0;
}

// function implements the first-fit algorithm
void first_fit(int p_size[], int n, int blockSize[], int m)
{
    memset(allocation, -1, sizeof(allocation)); // Initialize allocation array to -1
    // initially assigning -1 to all allocation indexes
    // signifies that there is presently no allocation
    for (int i = 0; i < n; i++)
    {
        allocation[i] = -1;
    }

    // systematically go through each procedure, looking for the first block that can accommodate it
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (blockSize[j] >= p_size[i])
            {
                // allocate block j to p[i] process
                allocation[i] = j;
                // Reduce size of block j as it has acc
                blockSize[j] -= p_size[i];
                break;
            }
        }
    }
}

// creates a tabular representation of the allocation table
// containing columns for the allocated block number, process size, and process number.
void memoryAllotedTable(int p_size[], int allocation[], int n)
{

    printf("\n\n");
    printf("`````````````````````````````````````````````````````````````````\n");
    printf("|Process No.\t\tProcess Size\tAllocated Block no.    |\n");
    printf("````````````````````````````````````````````````````````````````\n");
    for (int i = 0; i < n; i++)
    {
        printf("| %i\t\t\t", i + 1);
        printf("%i\t\t\t", p_size[i]);
        if (allocation[i] != -1)
            printf("%i \t       |", allocation[i] + 1);
        else
            printf("Not Allocated  |");
        printf("\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    }
}

// calculates the total amount of memory allotted to the processes, then returns it.
int memorySizeUsed(int p_size[], int n)
{
    int total_allocated_memory = 0;
    for (int i = 0; i < n; i++)
    {
        if (allocation[i] != -1)
        { // If process is allocated
            total_allocated_memory += p_size[i];
        }
    }

    return total_allocated_memory;
}

// calculates and displays the number of allocated blocks.
void block_displaying(int allocation[], int m)
{
    int num_allocated = 0;
    for (int i = 0; i < m; i++)
    {
        if (allocation[i] != -1)
        {
            num_allocated++;
        }
    }
    printf("Allocated_blocks: %d\n", num_allocated);
}

// determines and returns the quantity of unused (unallocated) blocks following allocation.

int wastedBlocks(int allocation[], int m)
{
    int wasted_blocks = 0;
    for (int i = 0; i < m; i++)
    { // For each memory block
        if (allocation[i] == -1)
        { // If block is not allocated
            wasted_blocks++;
        }
    }
    return wasted_blocks;
}

// after allocation, shows how much memory (blocksizes) is left for each block.

void memoryLeft(int blockSize[], int m)
{
    printf("\nBlock No.    Remaining memory after allocation\n\n");
    for (int i = 0; i < m; i++)
    {
        printf("   %d\t\t\t    %d\n", i + 1, blockSize[i]);
    }
}

// calculates and returns the total fragmentation of the blocks.
float fragmentation(int blockSize[], int m, int destArray[])
{
    int total_fragmentation = 0;
    for (int i = 0; i < m; i++)
    {
        if (blockSize[i] != destArray[i])
        {
            total_fragmentation += blockSize[i];
        }
    }

    return total_fragmentation;
}

// calculates and returns the average fragmentation of the blocks.
float avg_fragmentatioon(int total_fragmentation, int n)
{

    return (float)total_fragmentation / n * 100;
}
