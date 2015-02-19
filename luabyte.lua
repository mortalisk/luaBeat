
function tokenize(str)
  local par = 0
  local par_start = -1
  local tokens = {}
  local index = 0
  local prev = "" 
  function search(c)
    index = index + 1
    if c == "(" then
      if par == 0 then
        par_start = index
      end
      par = par + 1
    elseif c == ")" then
      par = par - 1
      if par == 0 then
        local t = str:sub(par_start+1, index)
        table.insert(tokens, tokenize(t))
        par_start = -1
        return
      end
    end
    
    if par == 0 then
      if c == "<" then 
        if prev == "<" then
          table.insert(tokens, "<<")
        end
      elseif c == ">" then
        if prev == ">" then
          table.insert(tokens, ">>")
        end
      else
        print("inserting " .. c)
        table.insert(tokens, c)
      end
    end
    prev = c
  end
  str:gsub(".",search)
  
  return tokens
  
end

function printt(t)
  io.write("[")
  for i, v in ipairs(t) do
    if type(v) == "table" then
      printt(v)
    else
      io.write(v .. ",")
    end
  end
  io.write("]")
end
	  