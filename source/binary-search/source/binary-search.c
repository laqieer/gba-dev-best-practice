
#include <gba_console.h>
#include <gba_video.h>
#include <gba_interrupt.h>
#include <gba_systemcalls.h>
#include <gba_input.h>
#include <stdio.h>
#include <stdlib.h>

int search(const int* nums, int numsSize, int target);

#define NUMS_SIZE 6
const int nums[NUMS_SIZE] = {-1,0,3,5,9,12};

//---------------------------------------------------------------------------------
// Program entry point
//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------
	int target;

	// the vblank interrupt must be enabled for VBlankIntrWait() to work
	// since the default dispatcher handles the bios flags no vblank handler
	// is required
	irqInit();
	irqEnable(IRQ_VBLANK);

	consoleDemoInit();

	iprintf("Binary Search:\n");
	iprintf("nums = [-1,0,3,5,9,12]\n");
	// case 1
	target = 9;
	iprintf("target = %d\n", target);
	iprintf("result = %d\n", search(nums, NUMS_SIZE, target));
	// case 2
	target = 2;
	iprintf("target = %d\n", target);
	iprintf("result = %d\n", search(nums, NUMS_SIZE, target));

	while (1) {
		VBlankIntrWait();
	}
}

int search(const int* nums, int numsSize, int target) {
    int l, r, mid;
    for (l = 0, r = numsSize - 1; l <= r; ) {
        mid = l + ((r - l) >> 1);
        if (nums[mid] == target) {
            return mid;
        }
        if (nums[mid] < target) {
            l = mid;
        } else {
            r = mid;
        }
    }
    return -1;
}
