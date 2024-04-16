# Baby Photoshop

### Tools
- | Qt | 6.5.3 |
- Microsoft Vs 2022
- CLion

___

### **Filters**
1. Grayscale
2. Black And White
3. Invert
4. Merge
5. Flip
6. Rotate
7. Darken & Brighten 
8. Crop
9. Add a frame
10. Detect image edges
11. Resize
12. Blur 
13. Sunlight
14. Oil painting
15. Old TV 
16. Purple 
17. Infrared 
18. Skew 
19. Bloom 
20. Gamma

___

### New Filters

1. #### Gamma
   • For each pixel in the image:

         • Normalize the color intensity by dividing it by 255.0.
   
         • Apply gamma correction to the normalized color intensity using the formula: color = pow(color, gamma).
   
         • Scale the corrected color intensity back to the range [0, 255] and assign it to the pixel.


2. #### Bloom
   1. Create a blurred imaged with radius of 2
   2. Iterate on each pixel
      1. Check if any channel of the pixel colors is greater than the threshold
         1. pixel [r] = min(255, pixel[r] * intensity + blurred [r])
         2. pixel [g] = min(255, pixel[g] * intensity + blurred [g])
         3. pixel [b] = min(255, pixel[b] * intensity + blurred [b])

___

### Sources :
1. #### Google Drive link for videos of new 2 filters:     https://drive.google.com/drive/folders/1qAbu3M0497vEp9O42b9CVE_qcn9SliBV
            (Bloom & Gamma Filter)
