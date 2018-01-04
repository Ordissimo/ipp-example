# ipp-example

This repository contains sample code which makes use of [CUPS][1] API to work/test the IPP functionality.

## Files

- `get-printer-attributes.c`: Every IPP printer/server has some attributes which a user/client can see using an IPP request(very similar to an HTTP GET request). For instance, if the name of my printer is **"My cool printer"**, there will be an attribute in the request with the name `printer-name` having value `My cool printer`.<br><br>To test this, you either need an IPP supported printer, or you can simulate a printer using the command `ippserver "My cool printer"`. This command makes use of the [`ippserver`][2] program.

## Compilation Instructions

You need `libcups2-dev` installed for the CUPS API. You can install it using `sudo apt install libcups2-dev` on linux systems. Then run:


```bash
make all
```

## Resources

1. [Introduction to CUPS Programming](https://www.cups.org/doc/api-overview.html)
2. [CUPS Programming Manual](https://www.cups.org/doc/cupspm.html)
3. [CUPS HTTP and IPP APIs](https://www.cups.org/doc/api-httpipp.html)
4. [CUPS Documentation](https://www.cups.org/documentation.html)
5. [ippsample Project](http://istopwg.github.io/ippsample/index.html)

[1]: https://www.cups.org
[2]: http://istopwg.github.io/ippsample/ippserver.html
