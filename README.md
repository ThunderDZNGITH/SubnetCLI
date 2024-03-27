# Subnet CLI

Ce programme en C++ permet de calculer les informations sur les sous-réseaux IPv4 à partir d'une adresse IP et de la notation CIDR.

## Fonctionnalités

- Conversion d'une adresse IP en binaire.
- Calcul du nombre d'hôtes possibles dans un sous-réseau.
- Obtention de la liste des sous-réseaux disponibles.

## Utilisation

Pour utiliser le programme, suivez ces étapes :

1. Clonez ce dépôt sur votre machine locale.
4. Exécutez le programme en spécifiant l'adresse IP et la notation CIDR en ligne de commande.

   Exemple d'utilisation :

```bash
./subnet_calculator -ip 192.168.1.1 -cidr 24
```

## Compilation

1. Installez gcc
   ```bash
   sudo apt-get install build-essential
   ```
2. Modifiez les droits du script de compilation
   ```bash
   chmod 777 run.sh
   ```
3. Lancez le script de compilation
   ```bash
   ./run.sh
   ```

## Documentation

La documentation complète du programme peut être générée à l'aide de Doxygen. Consultez les commentaires de documentation dans le code source pour plus de détails.

## Contributions

Les contributions sous forme de pull requests sont les bienvenues. Pour les changements majeurs, veuillez ouvrir d'abord une issue pour discuter de ce que vous souhaitez modifier.

## Licence

Ce programme est distribué sous la licence Apache 2.0. Consultez le fichier LICENSE pour plus d'informations.
