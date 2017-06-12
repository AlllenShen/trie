#coding : utf-8

def del_last_space(str):
	str_list = list(str)
	str_list.pop()
	return ''.join(str_list)

def add_linenum(file='wordlist.txt'):
	with open(file, 'r+') as f:
		i = 1
		rewrite = True
		lines = f.readlines()
		for line in lines:
			li = line.split(' ')
			if li[0].isdigit():
				rewrite = False
				break
			li.insert(0, '%d' % i)
			new_line = ''
			for item in li:
				new_line = new_line + item + ' '				
			lines[i-1] = del_last_space(new_line)
			print(lines[i-1])
			i += 1
		f.seek(0)
		if rewrite is True:
			f.writelines(lines)		
		
if __name__ == '__main__':
	add_linenum()
