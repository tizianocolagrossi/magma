#! /usr/bin/python3
import subprocess
import sys
import os

# set logging enabled on

def run_program_with_gdb(path_program, path_crash, log_file):
    gdb_script = '''
    
    skip -gfi 'stdlib/*.c'
    skip -gfi 'libio/*.c'
    skip -gfi 'nptl/*.c'
    skip -gfi 'stdio-common/*.c'
    skip -gfi 'instrumentation/*.c'
    skip -gfi 'sysdeps/*.c'
    skip -gfi '../sysdeps/**/*.c'
    skip -gfi 'sysdeps/**/*.c'
    skip -gfi 'bits/*.c'
    skip -gfi 'bits/*.h'
    
    set $_exitcode = -1
    set pagination off
    set logging file {}
    set logging on
    start
    while $_exitcode == -1
        step
        if $_exitcode != -1
            # If the program has exited, break the loop
            quit
        end
    end
    quit
    '''.format(log_file)

    # Write the GDB commands to a temporary file
    gdb_script_file = "gdb_script.txt"
    with open(gdb_script_file, "w") as file:
        file.write(gdb_script)

    # Run GDB with the script file
    cmd = f"gdb -nx -q -x {gdb_script_file} --args {path_program} {path_crash}"
    subprocess.run(cmd, shell=True)
    
    os.remove(f'./{gdb_script_file}')
    
    
    

if __name__ == "__main__":
    path_program = sys.argv[1]
    path_crash = sys.argv[-1]
    crash_name = os.path.basename(path_crash)
    
    print(sys.argv)

    
    log_file = f"/output/{crash_name}_gdb.log" 
    run_program_with_gdb(path_program, path_crash, log_file)