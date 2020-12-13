# png_vault
Uses steging to hide files in a .png picture
## Compiling
```
$ make
```
## Using
### Embeding
```
$ ./png_vault e test.txt example0.png example1.png
```
This will take test.txt and embed it into example0.png and rewrite it as example1.png
### Extracting
```
$ ./png_vault d example1.png test.txt
```
This will extract whatever is in example1.png and write it to test.txt
