import CToolKit as ct

STARTER  = f'COTP/COTP_main.h'

OUTPUT = 'COTPgenerator.h'
amalgamated_code = ct.generate_amalgamated_code(STARTER,OUTPUT)
