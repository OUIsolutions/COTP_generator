import Build.CToolKit as ct
from Build.full_folder_zip import zip_folder
from os import remove

EXEMPLES = 'exemples'
OUTPUT = 'COTPgenerator.h'
STARTER = f'COTP/COTP_main.h'


def execute_copilation(file:str,remove_output:bool):
    try:
        output = ct.compile_project(file)
        if remove_output:
            remove(output)
        return output
    except ct.CopilationWarning as e:
        remove(output)
        raise e

    except Exception as e:
        raise e

def sanitize_value(value:str)->str:
    lines = value.split('\n')
    lines = list(map(lambda x :x.strip(),lines))
    return ''.join(lines)

def test_execution(file:str,expected_output:str):
    output = execute_copilation(file,False)
    try:
        result = ct.ComandLineExecution(output)
    except Exception as e:
        remove(output)
        raise e
    remove(output)


    if sanitize_value(result.output) != sanitize_value(expected_output):
        raise Exception(f'output of {file} diferent')
    print(f'passed: {file}')

def test_static_key_generation():
    test_execution(
        f'{EXEMPLES}/static_key_generation.c',
        '94adef2de017bea53aa810a8a08ddd1c277bd93b63ce0e1ad48ea4bd24ecc30100000060201'
    )

def test_static_password():
    test_execution(
        f'{EXEMPLES}/static_password.c',
        """
        key: a4aadfa1a3a33bd6dd74
        time remaning: 59
        """
    )
def test_static_custom_password():
    test_execution(
        f'{EXEMPLES}/static_custom_password.c',
        """
        key: 1733211172
        time remaning: 1799
        """
    )

def test_static_custom_key():
    test_execution(
        f'{EXEMPLES}/static_custom_key.c',
       '14817323945224231901655816816168160141200001800100'
    )

def test_exemples():
    ct.generate_amalgamated_code(STARTER,f'{EXEMPLES}/{OUTPUT}')
    ct.execute_test_for_file(f'{EXEMPLES}/random_key_generation.c')
    print("passed: random_key_generation.c")
    execute_copilation(f'{EXEMPLES}/password_generation.c',True)
    execute_copilation(f'{EXEMPLES}/custom_key.c',True)
    print('passed: custom_key.c')
    test_static_key_generation()
    test_static_password()
    test_static_custom_key()
    test_static_custom_password()




test_exemples()
amalgamated_code = ct.generate_amalgamated_code(STARTER,OUTPUT)
ct.include_code_in_markdown('README.md',True)


zip_folder('COTP_Generator')