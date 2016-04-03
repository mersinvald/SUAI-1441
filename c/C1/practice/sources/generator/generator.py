__author__ = 'mike'
import sys


class Cell:
	type = 0
	isborder = False
	def __init__(type = 0, border = False):
		type = type
		isborder = border

def print(grid):
	for level in grid:
		for cell in level:
			print(("X" if cell.isborder else " "))
		print("\n")

def makelevel()

args = sys.argv

width  = int(args[1])*2 + 2
heigth = int(args[2])*2 + 2

grid = []


level = []							#Make top borders wall
for i in range(0, width):
	level.append(Cell(border=True))
grid.append(level)

