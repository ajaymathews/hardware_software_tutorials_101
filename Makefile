SUBDIRS = $(wildcard DEVICE_DRIVER/*)

all:
	@for dir in $(SUBDIRS); do \
		if [ -f $$dir/Makefile ]; then \
			echo "Building in $$dir..."; \
			$(MAKE) -C $$dir; \
		fi; \
	done

clean:
	@for dir in $(SUBDIRS); do \
		if [ -f $$dir/Makefile ]; then \
			echo "Cleaning in $$dir..."; \
			$(MAKE) -C $$dir clean; \
		fi; \
	done

.PHONY: all clean
