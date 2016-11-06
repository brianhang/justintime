-- Lua test stage.

-- "stage" is a table that contains information about the current stage.

-- Called when the stage starts.
function stage:init()
    print("Started test stage")

    for i = 1, 5 do
        print(i)
    end

    self.i = 1
end

local function printTable()
for k,v in pairs(io) do
    print(k, v)
    end
end

-- Called every frame to update the state of the stage.
function stage:update(deltaTime)
    print(self.i)
    self.i = self.i + (30 * deltaTime)

end

-- Called every frame to draw stuff to the screen.
function stage:draw()
    local sides = math.sin(self.i * 0.1) * 8 + 11
    draw.setColor(255, 0, 255)
    draw.setRotation(0)
    draw.polygon(64, 64, 32, sides)

    draw.setRotation(45)
    draw.setColor(255, 50, 50, 125)
    draw.rectangle(self.i, 60+math.cos(self.i*0.2)*30, 128, 128)
    draw.line(320,240,math.cos(self.i)*960,math.sin(self.i)*720)
    draw.text(200-self.i, 300-self.i, "Biblioteca", "pressstart2p", 10)
end

-- Called when the stage has ended.
function stage:exit()
    print("Wow")
end

printTable()
