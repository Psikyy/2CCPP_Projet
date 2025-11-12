# 2CCPP_Projet
Projet C++ 2ème année SUPINFO

Bienvenue dans le jeu The Devil's Plan.

Cher joueur,

Voici comment se déroule une partie : chaque joueur joue à tour de rôle en plaçant des tuiles de différentes formes.
L’objectif est simple : former le plus grand carré possible.
À la fin de la partie, le joueur possédant le carré avec le plus grand côté remporte la victoire.

Le déroulement du jeu

À votre tour, vous pouvez effectuer différentes actions :
-   Poser une tuile : c’est l’action principale. Une fois la tuile placée, votre tour se termine.
-   Faire pivoter (tourner) ou retourner une tuile pour l’orienter comme vous le souhaitez.
-   Utiliser un coupon pour bénéficier d’un avantage stratégique.
-   Afficher les prochaines tuiles afin d’anticiper vos placements.
-   Passer votre tour si vous ne souhaitez ou ne pouvez pas jouer.

Les bonus

Le plateau contient plusieurs cases spéciales symbolisées par des lettres (et non par des points).
Ces cases représentent des bonus que vous pouvez obtenir en les entourant entièrement avec vos tuiles.
Attention : si vous posez une tuile directement sur la case du bonus, celui-ci disparaîtra sans effet.

Les différents bonus :

Pierre (P)
Une fois récupérée, elle peut être placée n’importe où sur le plateau afin de bloquer une zone ou gêner un adversaire.

Coupon (E)
Il vous offre un échange spécial.
Lorsque vous utilisez un coupon, vous pouvez choisir :
-   De retirer une pierre présente sur le plateau.
-   De changer la prochaine tuile que vous allez recevoir parmi les 5 suivantes de la pioche.

Vol (V)
Ce bonus vous permet de voler une tuile appartenant à un adversaire directement sur le plateau.

Règles supplémentaire.

-   Vous ne pouvez pas superposer une tuile sur une autre déjà posée.
-   Vos tuiles doivent toucher votre territoire par un côté (et non uniquement par un coin).
-   Les pierres bloquent toute pose sur leur case, sauf si elles sont retirées à l’aide d’un coupon.
-   Vous pouvez cumuler plusieurs coupons au cours de la partie.
-   La partie se termine lorsque toutes les tuiles ont été jouées ou qu’aucun joueur ne peut plus poser de tuile.

Fin de partie

À la fin du jeu, on calcule pour chaque joueur :
la taille du plus grand carré formé avec ses tuiles,
et, en cas d’égalité, le nombre total de cases occupées.
Celui qui possède le carré le plus grand (ou, à égalité, le plus grand territoire total) est déclaré vainqueur.