#include <inc/memlayout.h>
#include <kern/kheap.h>
#include <kern/memory_manager.h>

//2016: NOTE: All kernel heap allocations are multiples of PAGE_SIZE (4KB)
uint32 * firstFreeVAInKHeap  = NULL;
void* kmalloc(unsigned int size)
{
	uint32* returnVal = NULL;
	if(firstFreeVAInKHeap == NULL)
		firstFreeVAInKHeap = (uint32*) KERNEL_HEAP_START;

	if((int) (&firstFreeVAInKHeap)+size>KERNEL_HEAP_MAX)
		return returnVal;

	int i;
	int PhysicalAddress;
	for(i=0;i<size;i+=PAGE_SIZE){
		struct Frame_Info * ptr;
		PhysicalAddress = allocate_frame(&ptr);
		map_frame(ptr_page_directory,ptr,firstFreeVAInKHeap,PERM_PRESENT);
		if(i==0)returnVal=firstFreeVAInKHeap;
		firstFreeVAInKHeap+=PAGE_SIZE;
	}
	return returnVal;
	//TODO: [PROJECT 2016 - Kernel Dynamic Allocation/Deallocation] kmalloc()
	// Wptrrite your code here, remove the panic and write your code
	//panic("kmalloc() is not implemented yet...!!");

	//NOTE: Allocation is continuous increasing virtual address
	//NOTE: All kernel heap allocations are multiples of PAGE_SIZE (4KB)
	//refer to the project documentation for the detailed steps


	//TODO: [PROJECT 2016 - BONUS1] Implement a Kernel allocation strategy
	// Instead of the continuous allocation/deallocation, implement one of
	// the strategies NEXT FIT, BEST FIT, .. etc


	//change this "return" according to your answer
	//return 0;
}

void kfree(void* virtual_address)
{
	uint32 * ptr_page_table;
	get_page_table(ptr_page_directory,(void*) virtual_address,&ptr_page_table);
	uint32 physicalAddress = ptr_page_table[PTX(virtual_address)] >> 12;
	ptr_page_table[PTX(virtual_address)];
	struct Frame_Info * ptr = to_frame_info(physicalAddress);
	free_frame(ptr);
	ptr_page_table[PTX(virtual_address)]= 0;
	//TODO: [PROJECT 2016 - Kernel Dynamic Allocation/Deallocation] kfree()
	// Write your code here, remove the panic and write your code
	//panic("kfree() is not implemented yet...!!");

	//get the size of the given allocation using its address
	//refer to the project documentation for the detailed steps

	//TODO: [PROJECT 2016 - BONUS1] Implement a Kernel allocation strategy
	// Instead of the continuous allocation/deallocation, implement one of
	// the strategies NEXT FIT, BEST FIT, .. etc

}

unsigned int kheap_virtual_address(unsigned int physical_address)
{

	uint32 *ptr_page_table = NULL;

	uint32 va = 0;
	while(1 == 1) {
		ptr_page_table = NULL;
		get_page_table(ptr_page_directory,(void*) va,&ptr_page_table);

		 uint32 actual = (ptr_page_table[PTX(va)] >> 12);
		 actual *= PAGE_SIZE;
			if(actual == physical_address)
				return va;
		va += PAGE_SIZE;
	}

	//TODO: [PROJECT 2016 - Kernel Dynamic Allocation/Deallocation] kheap_virtual_address()
	// Write your code here, remove the panic and write your code
	//panic("kheap_virtual_address() is not implemented yet...!!");

	//return the virtual address corresponding to given physical_address
	//refer to the project documentation for the detailed steps

	//change this "return" according to your answer
}

unsigned int kheap_physical_address(unsigned int virtual_address)
{
	uint32 *pageTable;
	get_page_table(ptr_page_directory,(void*)virtual_address,&pageTable);
	uint32 physicalAddress = pageTable[PTX(virtual_address)]>>12;
	return physicalAddress;
	//TODO: [PROJECT 2016 - Kernel Dynamic Allocation/Deallocation] kheap_physical_address()
	// Write your code here, remove the panic and write your code
	//panic("kheap_physical_address() is not implemented yet...!!");

	//return the physical address corresponding to given virtual_address
	//refer to the project documentation for the detailed steps

	//change this "return" according to your answer
	//return 0;
}
