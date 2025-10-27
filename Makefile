# Command line format: `make PORT=[serial modem port]`
# https://stackoverflow.com/a/2826178/6621292
esp32c3:
	cp sdkconfig.esp32c3 sdkconfig
	idf.py build flash monitor --port=$(PORT)

esp32h2:
	cp sdkconfig.esp32h2 sdkconfig
	idf.py build flash monitor --port=$(PORT)

clean:
	rm -r -f build
	idf.py fullclean