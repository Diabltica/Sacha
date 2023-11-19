import pygame
import sys
import asyncio
import websockets

# Initialisation de Pygame
pygame.init()

# Définir la taille de la fenêtre (non utilisée dans cet exemple)
size = (700, 500)
screen = pygame.display.set_mode(size)
pygame.display.set_caption("Detecteur de touches")

# Paramètres pour la communication WebSocket
websocket_uri = "ws://localhost:8765"  # Remplacez par votre URI WebSocket
async def send_data(websocket, data):
    await websocket.send(data)

# Valeurs par défaut
direction = 128
propulsion = 128
x_position = 128
y_position = 128

# Boucle principale
async def main():
    global direction, propulsion, x_position, y_position
    # Connecter au serveur WebSocket
    async with websockets.connect(websocket_uri) as websocket:
        while True:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    pygame.quit()
                    sys.exit()
                elif event.type == pygame.KEYDOWN or event.type == pygame.KEYUP:
                    # Récupérer la touche appuyée ou relâchée
                    keys = pygame.key.get_pressed()
                    propulsion = 128 if keys[pygame.K_a] else propulsion
                    # Mettre à jour les valeurs en fonction des touches appuyées
                    direction += 5 if keys[pygame.K_d] else -5 if keys[pygame.K_q] else 0
                    propulsion += 5 if keys[pygame.K_z] else -5 if keys[pygame.K_s] else 0
                    x_position += 5 if keys[pygame.K_LEFT] else -5 if keys[pygame.K_RIGHT] else 0
                    y_position += 5 if keys[pygame.K_UP] else -5 if keys[pygame.K_DOWN] else 0

                    # Limiter les valeurs entre 0 et 255
                    direction = max(0, min(255, direction))
                    propulsion = max(0, min(255, propulsion))
                    x_position = max(0, min(255, x_position))
                    y_position = max(0, min(255, y_position))

                    # Construire la trame
                    data = f"D{direction}P{propulsion}X{x_position}Y{y_position}"

                    # Afficher la trame dans la console
                    print(f"Trame envoyée : {data}")

                    # Envoyer la trame via WebSocket
                    
                    await send_data(websocket, data)

            # Ne pas oublier de mettre à jour la fenêtre (non utilisé dans cet exemple)
            pygame.display.flip()
            await asyncio.sleep(0.1)  # Ajout d'un délai pour éviter une consommation excessive du processeur

# Exécuter la boucle principale
if __name__ == "__main__":
    asyncio.run(main())
