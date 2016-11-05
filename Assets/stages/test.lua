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
    draw.setColor(255, 0, 0)
    draw.rectangle(self.i, 60+math.cos(self.i*0.2)*30, 128, 128)
end

printTable()
