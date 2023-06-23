import CToolKit as ct
from os import remove
EXEMPLES = 'exemples'
OUTPUT = 'COTPgenerator.h'
STARTER = f'COTP/COTP_main.h'

def execute_copilation(file:str,remove_output:bool):
    try:
        output = ct.compile_project('gcc',file)
        if remove_output:
            remove(file)
    except ct.CopilationWarning as e:
        remove(output)
        raise e

    except Exception as e:
        raise e

def test_static_generation():
    pass


def test_exemples():
    ct.generate_amalgamated_code(STARTER,f'{EXEMPLES}/{OUTPUT}')
    ct.execute_test_for_file('gcc',f'{EXEMPLES}/key_generation.c')
    print("key_generation passed")
    execute_copilation(f'{EXEMPLES}/password_generation.c',True)


test_exemples()
amalgamated_code = ct.generate_amalgamated_code(STARTER,OUTPUT)
