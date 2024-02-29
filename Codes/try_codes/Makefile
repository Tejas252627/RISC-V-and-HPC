CC = riscv64-unknown-elf-gcc

bin:
	$(CC) -c vvadd.s
	$(CC) -c main.c 
	$(CC) main.o vvadd.o -o main
	$(CC) novect.c -o novect

run:
	@-qemu-riscv64-static -cpu rv64,v=true main
	@-qemu-riscv64-static -cpu rv64,v=true novect


