
AddCh("Prince","Sumit")
--AddBg("Palace.bmp")
AddBg()
--sumit = {}

function situation()
	MyMessage("游戏开始")
	MyMessage("Space观看下一页对话\nBackSpace更换对话选项,\nEnter确认对话选项")
	print("function situation was called")
	--bg(1);
	dialog("房间里除了修米特，还能感觉到其他人的存在啊，一种被监视的感觉，真的是不自在啊，这么快就有人注意到我吗？ 一会儿面对修米特的时候，还是伪装一下比较好，或者是直接告诉他我的来意。。。。。。","王子","Prince");
	dialog( "不知道这里会不会有人注意到我……" , "王子","Prince");
	dialog( "这是一句囧话，","王子" , "Prince");
	dialog( "这又是另一句囧话笨蛋","王子", "Prince" );
	--print(sumit.goodwill)
	--choice is a c function, the result is the number of choice
	--dialog("房间里除了修米特，还能感觉到其他人的存在啊，一种被监视的感觉，真的是不自在啊，这么快就有人注意到我吗？ 一会儿面对修米特的时候，还是伪装一下比较好，或者是直接告诉他我的来意。。。。。。","王子","Prince");

	local rs = choice("以吟游诗人亚瑟尔的身份去见修米特","直接以公国大王子的身份去见修米特","囧囧")
	--rs = 1
	--dialog("房间里除了修米特，还能感觉到其他人的存在啊，一种被监视的感觉，真的是不自在啊，这么快就有人注意到我吗？ 一会儿面对修米特的时候，还是伪装一下比较好，或者是直接告诉他我的来意。。。。。。","王子","Prince");

	if rs == 1 then
		dialog("房间里除了修米特，还能感觉到其他人的存在啊，一种被监视的感觉，真的是不自在啊，这么快就有人注意到我吗？ 一会儿面对修米特的时候，还是伪装一下比较好，或者是直接告诉他我的来意。。。。。。","王子","Prince");
		dialog("吟游诗人。。。呵呵，亚瑟尔，这算是实现你曾经的梦想吗。。。。看来你了解到现在的情况了","修米特","Prince")
		dialog("修米特，这么长时间不见，你的生活还是那么享受啊。","王子","Prince")
		dialog("呵呵，享乐可是人生唯一的乐趣，不是吗？","修米特","Prince")
		dialog("说的很有道理啊，可是我最近却遇到了不小的麻烦呢。","王子",0)
		dialog("哦？我们幸运的亚瑟尔也会遇到麻烦，真是很不可思议呢。","修米特",0)
		dialog("在海盗绝迹的海域能遇见正规的海盗军队，也许这真是一种幸运呢。","王子",0)
		dialog("你应该是在说罗德王子遇袭的事情吧，这件事在爱德兰可是机密。","修米特",0)
		dialog("所以我现在站在了这里。","王子",0)
		dialog("这件事你了解了多少呢，亚瑟尔。","修米特",0)
		MyMessage("得到了囧戒指")

		sumit.goodwill = sumit.goodwill+1
	else
		dialog("房间里除了修米特，还能感觉到其他人的存在啊，一种被监视的感觉，真的是不自在啊，这么快就有人注意到我吗？ 一会儿面对修米特的时候，还是伪装一下比较好，或者是直接告诉他我的来意。。。。。。","王子","Prince");
		dialog("可恶，竟然这么招摇的进来。。。。。。我还是要掩饰一下。。。。。。但愿你能察觉到现在并不是你亮出身份的时候","王子","Prince")
		sumit.recognition = sumit.recognition+1
		--print("参数个数为"..rs)
		print(rs)
	end
	--print(sumit.goodwill)
	--dialog("")
	--return
end

print(text)
