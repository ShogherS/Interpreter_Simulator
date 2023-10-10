void Parser::removeSpace(size_t pos)
{
	data[pos].erase(std::remove_if(data[pos].begin(), data[pos].end(), ::isspace), data[pos].end()); 
}

