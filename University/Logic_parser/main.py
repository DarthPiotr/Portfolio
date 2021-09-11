# RPN to Infix 
one_arg = {'NOT', '~', '¬' }
two_arg = { 'AND', '&', '∧', 'OR', '|', '∨', 'TO', '→', 'IFF', '↔', 'XOR', '⊕' }
quantifiers = {'FORALL', '∀', 'EXISTS', '∃'}


while True:
   try:
      stack = []
      line = [ x for x in input().split() ]
      
      for element in line:
          temp = []
          if (element not in one_arg) and (element not in two_arg) and (element not in quantifiers):
            # variables
            if element.find('/') == -1:
                stack.append(element)
            # functions 
            else:
                name, args = element.split('/')
                # [name](stos[0], stos[1] ... , stos[args-1])
                name += '('
                args = int(args)
                for i in range(args):
                    name += stack.pop(len(stack) - args + i)
                    if i < args - 1:
                        name += ', '
                    else:
                        name += ')'
                stack.append(name)
          elif element in one_arg:
              name = '(' + element + ' ' + stack.pop() + ')'
              stack.append(name)
          elif element in two_arg:
              name = '(' + stack.pop(len(stack)-2) + ' ' + element + ' ' + stack.pop() + ')'
              stack.append(name)
          else:
              name = '(' + element + ' ' + stack.pop(len(stack)-2) + ' ' + stack.pop() + ')'
              stack.append(name)

      print(stack.pop())     
                    
   except EOFError:
      break