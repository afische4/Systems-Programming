
class Dataframe:
	def __init__(self):
		self.data = list()
		self.headers = list()

	def append(self, newdata):
		self.data.append(newdata)

	def set_headers(self, headers):
		self.headers = headers
