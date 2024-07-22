## Lab 6 casita GLut  Rotar y zoom

![image](https://github.com/user-attachments/assets/b466ea15-9b38-4b91-a34d-af720be778e7)
## Lab 7.1 Sectores circulares, usando rojo, verde, azul y Glut 
![image](https://github.com/user-attachments/assets/924f0f73-3550-466f-9400-37a12d60e1ae)

## 7.2 Diferencias entre Marching Cubes y Delaunay

|Característica|Marching Cubes|Delaunay|
|--------------|--------------|--------|
|Dimensionalidad|3D|2D y 3D|
|Entrada|Campo escalar discreto 3D (vóxeles)|Conjunto de puntos en 2D o 3D|
|Salida|Malla poligonal de una isosuperficie|Triangulación que satisface el criterio de Delaunay|
|Algoritmo|Divide el espacio en cubos, determina los polígonos necesarios para representar la isosuperficie que pasa por cada cubo, y fusiona los polígonos individuales en la superficie deseada|Construye una triangulación que satisface el criterio de Delaunay, el cual especifica que el círculo circunscrito de cada triángulo no contiene ningún otro punto en su interior|
|Aplicaciones|Visualización médica (CT, MRI), efectos especiales, modelado 3D|Generación de mallas para simulaciones de elementos finitos, modelado de terreno, estimación de densidad de puntos|
|Propiedades|Genera una malla poligonal que aproxima la isosuperficie|Genera una triangulación óptima según ciertos criterios geométricos, como evitar triángulos alargados|
