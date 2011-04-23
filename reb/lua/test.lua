if #arg == 0 then
	print("Usage: cat file | luajit test.lua")
	os.exit(1)
end

local pat = arg[1]
for l in io.lines() do
	if l:find(pat) then print(l) end
end
