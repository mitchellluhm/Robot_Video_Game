## Robot Simulator Iteration 1 Bug Report

#### Name: luhmx009 ( Mitchell Luhm )

### Current Bugs:
- **OBSTACLE** Some obstacles sometimes start moving before user hits "Start Game"
  - Why does this happen?
    - They Spawn close enough to another entity making a collision detection
  - How to Fix:
    - Ignore collisions when game is in IsPaused state (or not started).
- **GRAPHICARENAVIEWER** Playing button should not say "Playing" when game results in a win or loss.
  - How to Fix:
    - Just update the button's text if game is over.
    - Maybe check if game is over in GraphicArenaViewer::UpdateSimulation()
- **GRAPHICARENAVIEWER**Segmentation fault reported when user exits GUI window.
- **REST OF FILES** no *known* bugs with respect to the requirements I attempted.

### Current TODOs:
- Number of lives remaining should show in robot's body

### Cleaner Code Ideas
- PARAM for max speed / use one...
- PARAM for lives
- Check robot for set\_speed\_delta
- Print "Winner" and "Loser" Center of Screen, better text color
- Implement ResumeSpeed() and PauseSpeed() once
- if conditions in Controller::ConvertComm()
