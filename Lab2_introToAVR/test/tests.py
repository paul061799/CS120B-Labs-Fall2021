# Array of tests to run (in order)
# Each test contains
#   description - 
#   steps - A list of steps to perform, each step can have
#       inputs - A list of tuples for the inputs to apply at that step
#       *time - The time (in ms) to wait before continuing to the next step 
#           and before checking expected values for this step. The time should be a multiple of
#           the period of the system
#       *iterations - The number of clock ticks to wait (periods)
#       expected - The expected value at the end of this step (after the "time" has elapsed.) 
#           If this value is incorrect the test will fail early before completing.
#       * only one of these should be used
#   expected - The expected output (as a list of tuples) at the end of this test
# An example set of tests is shown below. It is important to note that these tests are not "unit tests" in 
# that they are not ran in isolation but in the order shown and the state of the device is not reset or 
# altered in between executions (unless preconditions are used).
tests = [ {'description': 'Over 140kg: PINA: 50, PINB: 50, PINC: 50 => PORTD: 0x25',
    'steps': [ {'inputs': [('PINA',50), ('PINB', 50), ('PINC', 50)], 'iterations': 5 } ],
    'expected': [('PORTD',0x25)],
    },
    {'description': 'Exceed 80kg Diff: PINA: 5, PINB: 25, PINC: 90 => PORTD: 0x1E',
    'steps': [ {'inputs': [('PINA',5), ('PINB', 25), ('PINC', 90)], 'iterations': 5 } ],
    'expected': [('PORTD',0x1E)],
    },
    {'description': 'Both: PINA: 5, PINB: 55, PINC: 90 => PORTD: 0x27',
    'steps': [ {'inputs': [('PINA',5), ('PINB',55), ('PINC',90)], 'iterations': 5 } ],
    'expected': [('PORTD',0x27)],
    },
	{'description': 'Neither: PINA: 45, PINB: 30, PINC: 45 => PORTD: 0x1C',
    'steps': [ {'inputs': [('PINA',45), ('PINB',30), ('PINC',45)], 'iterations': 5 } ],
    'expected': [('PORTD',0x1C)],
    },
    ]


# Optionally you can add a set of "watch" variables these need to be global or static and may need
# to be scoped at the function level (for static variables) if there are naming conflicts. The 
# variables listed here will display everytime you hit (and stop at) a breakpoint
watch = ['PORTD']

