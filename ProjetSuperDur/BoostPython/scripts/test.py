# test.py ---------------------------------------------------------
print("test.py : script démarré 🚀")

class Calculatrice:
    def __init__(self, base: int = 0):
        self.base = base

    def ajoute(self, x: int) -> int:
        self.base += x
        return self.base

def faire_truc(a: int, b: int) -> int:
    """
    Additionne deux entiers, affiche le calcul côté Python
    et retourne le résultat.
    """
    resultat = a + b
    print(f"[Python] Calcul : {a} + {b} = {resultat}")
    return resultat

if __name__ == "__main__":
    # Petit auto‑test
    res = faire_truc(2, 3)
    print("[Python] Résultat auto‑test :", res)
# ----------------------------------------------------------------