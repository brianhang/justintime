-- Lua test stage.

-- "stage" is a table that contains information about the current stage.

-- Called when the stage starts.
function stage:init()
    print("Woo it's stage 1!")
end

-- Called every frame to draw stuff to the screen.
function stage:draw()
    draw.setColor(255, 255, 255)
    draw.rectangle(0, 0, 640, 480)
end
