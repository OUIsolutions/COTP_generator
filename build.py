import CToolKit as ct

STARTER = f'COTP/COTP_main.h'

OUTPUT = 'COTPgenerator.h'
result =amalgamated_code = ct.generate_amalgamated_code(STARTER,OUTPUT)

with open(f'exemples/{OUTPUT}','w') as arq:
    arq.write(result)
