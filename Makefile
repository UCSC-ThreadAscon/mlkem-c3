esp32c3:
	cp sdkconfig.esp32c3 sdkconfig

esp32h2:
	cp sdkconfig.esp32h2 sdkconfig

clean:
	rm -r -f build
	idf.py fullclean