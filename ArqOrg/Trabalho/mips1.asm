.data  
fin: .asciiz "test.txt"      # filename for input
buffer: .space 128
buffer1: .asciiz "\n"
val : .space 128
newline: .asciiz "\n"
ans: .asciiz " The String reversed is "
.text

################################################ fileRead:

# Open file for reading

li   $v0, 13       # system call for open file
la   $a0, fin      # input file name
li   $a1, 0        # flag for reading
li   $a2, 0        # mode is ignored
syscall            # open a file 
move $s0, $v0      # save the file descriptor 

# reading from file just opened

li   $v0, 14       # system call for reading from file
move $a0, $s0      # file descriptor 
la   $a1, buffer   # address of buffer from which to read
li   $a2,  11  # hardcoded buffer length
syscall            # read from file

#li  $v0, 4          # 
la  $a0, buffer     # buffer contains the values
syscall             # print int

lb $t1 , buffer


la      $a0, buffer     #calling opening prompt
#li      $v0, 4
syscall
la      $a0, buffer        #initial string
syscall
la      $a0, newline    #newline
syscall
la      $a0, ans        #initial text for reversed string
syscall
li      $t2, 0
strLen:                 #getting length of string
lb      $t0, buffer($t2)   #loading value
add     $t2, $t2, 1
bne     $t0, $zero, strLen

li      $v0, 11         #load immediate - print low-level byte
Loop:
sub     $t2, $t2, 1     #this statement is now before the 'load address'
la      $t0, buffer($t2)   #loading value
lb      $a0, ($t0)
syscall
#This is where the sub statement used to be, which caused the loop to terminate too early
bnez    $t2, Loop
li      $v0, 10              #program done: terminating
syscall



# Close the file 

li   $v0, 16       # system call for close file
move $a0, $s6      # file descriptor to close
syscall            # close file