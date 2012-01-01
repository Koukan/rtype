all	:
	make -C common/
	make -C client/

clean	:
	make clean -C client/

fclean	:
	make fclean -C client/

re	: fclean all

libclean:
	make clean -C common/

libfclean:
	make fclean -C common/

libre:
	make re -C common/
