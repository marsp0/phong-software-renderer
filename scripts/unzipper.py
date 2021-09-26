from zipfile import ZipFile
import argparse

def main(zip_path, extract_path):
	archive = ZipFile(zip_path)
	archive.extractall(extract_path)

if __name__ == '__main__':
	parser = argparse.ArgumentParser()
	parser.add_argument('-zp')
	parser.add_argument('-ep')
	args = parser.parse_args()
	main(args.zp, args.ep)