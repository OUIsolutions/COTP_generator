import CToolKit as ct
from os import remove
EXEMPLES = 'exemples'
OUTPUT = 'COTPgenerator.h'
STARTER = f'COTP/COTP_main.h'


def execute_copilation(file:str,remove_output:bool):
    try:
        output = ct.compile_project('gcc',file)
        if remove_output:
            remove(output)
        return output
    except ct.CopilationWarning as e:
        remove(output)
        raise e

    except Exception as e:
        raise e

def test_execution(file:str,expected_output:str):
    output = execute_copilation(file,False)
    try:
        result = ct.ComandLineExecution(output)
    except Exception as e:
        remove(output)
        raise e
    remove(output)

    if result.output.strip() != expected_output:
        raise Exception(f'output of {file} diferent')
    print(f'passed: {file}')

def test_static_generation():
    test_execution(
        f'{EXEMPLES}/static_generation.c',
        '94adef2de017bea53aa810a8a08ddd1c277bd93b63ce0e1ad48ea4bd24ecc30100000060201'
    )


def test_exemples():
    ct.generate_amalgamated_code(STARTER,f'{EXEMPLES}/{OUTPUT}')
    ct.execute_test_for_file('gcc',f'{EXEMPLES}/key_generation.c')
    print("passed: key_generation.c")
    execute_copilation(f'{EXEMPLES}/password_generation.c',True)
    print('passed: password_generation.c')
    test_static_generation()

test_exemples()
amalgamated_code = ct.generate_amalgamated_code(STARTER,OUTPUT)
