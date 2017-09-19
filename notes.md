Edit:
-----

Estas son dudas sobre el enunciado de la tarea y un pequeño resumen del mismo, al final de cuentas no se implementó la fución de preprocesador.


Resumen de enunciado
--------------------

	C -> scanner -> beamer


generacion archivo temporal (preprocesador)
-------------------------------------------
	
	C -> preprocesador -> archivo temporal

	reglas del preprocesador de c
		#include
			incluir archivo dentro del directorio como parte del fuente
			el nuevo archivo puede tener nuevas directivas a procesar
		#define
			nombre que sigue mismas reglas que variables, nombres que aparecen en el fuente
			deben ser reemplazados por la hilera dentro del #define
			NO se manejan macros con parametros (seria extra)


analisis lexico
---------------
	
	C -> archivo temporal -> scanner -> beamer

	relativamente facil con *flex*
	escribir un scanner para el lenguaje de C completo, segun la documentacion de c
	algo asi como hacer una funcion `Get_Token()`
		al ser invocada regresa el siguiente token del fuente, en alguna estructura de datos
		apropiada, con cosas como: codigo de token, puntero al lexema, valor numerico del
		lexema, etc

		**recomendable hacer el `Get_Token()` reusable para futuros proyectos**
	
	El beamer puede ser apartir de varios archivos
		- estatico
		- lexemas en formato latex generado por scanner
		- histograma generado por gnuplot apartir de archivo generado por scanner?

		C -> temporal -> scanner -> lexemas                                -> beamer
								 -> archivo datos -> gnuplot -> histograma ->
								 -> estatico                               ->

salida
------

	C -> temporal -> scanner -> Latex source -> beamer

	presentacion beamer de latex
	internamente ejecutar comando `pdflatex`
	desplegarlo de inmendiato (probalemente usand el comando `evince`) en fullscreen

	presentacion beamer
		gran calidad, tablas, colores, dibujos, imagenes, graficos
		- portada
		- explicacion del proceso de scanning y la herramienta flex
		- slides del codigo temporal/intermedio, distincion de cada lexema
			utilizar tipos de letra, pesos, italics, colores (fg, bg)
			reportar errores lexicos
		- cantidad razonable del codigo original en cada slide
		- histograma de las cantidades de cada tipo de token
			se puede preparar internamente un archivo de datos
			invocar el comando gnuplot desde el programa
			o utilizar el package pdfplots de latex


Dudas
=====

	presentacion en beamer:
		hay partes estaticas y el resto se genera con el scanner, right?
		como determinar cuanto codigo por slide?
		codigo original y el temporal en el mismo slide?
		output del scanner serian los archivos para el beamer y tambien compilarlos a latex y hacerles display?
