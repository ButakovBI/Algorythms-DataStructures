import pytest
from parser.utils import to_snake_case, split_tags, convert_tags_to_semi_colon


@pytest.mark.asyncio
async def test_to_snake_case_basic():
    assert to_snake_case("DisplaySvc") == "Display_Svc"
    assert to_snake_case("SimpleTag") == "Simple_Tag"
    assert to_snake_case("Tag") == "Tag"
    assert to_snake_case("TagTag") == "Tag_Tag"


@pytest.mark.asyncio
async def test_to_snake_case_edge_cases():
    assert to_snake_case("aBC") == "a_BC"
    assert to_snake_case("HTMLParser") == "HTML_Parser"
    assert to_snake_case("HTML") == "HTML"
    assert to_snake_case("Ha") == "Ha"
    assert to_snake_case("aH") == "a_H"
    assert to_snake_case("H_a") == "H_a"
    assert to_snake_case("___") == "___"
    assert to_snake_case("abcDed_faFx_e") == "abc_Ded_fa_Fx_e"
    assert to_snake_case("    ") == ""
    assert to_snake_case("a    ") == "a"
    assert to_snake_case("    f") == "f"
    assert to_snake_case("    fAf") == "f_Af"
    assert to_snake_case("F   ") == "F"
    assert to_snake_case("   Faaa") == "Faaa"
    assert to_snake_case("") == ""


@pytest.mark.asyncio
async def test_split_tags_basic():
    assert await split_tags("web_engine; AUTO") == {"web", "engine", "AUTO", "web_engine"}
    assert await split_tags("tag1 ; tag2 ; tag3") == {"tag1", "tag2", "tag3"}
    assert await split_tags("tag1;tag2;tag3") == {"tag1", "tag2", "tag3"}
    assert await split_tags("tag1;tag2; tag3") == {"tag1", "tag2", "tag3"}
    assert await split_tags("tag1_tag2_tag3") == {"tag1", "tag2", "tag3", "tag1_tag2_tag3"}


@pytest.mark.asyncio
async def test_split_tags_empty_string():
    assert await split_tags("") == set()


@pytest.mark.asyncio
async def test_split_tags_with_extra_spaces():
    assert await split_tags("  tag1;  tag2  ; tag3  ") == {"tag1", "tag2", "tag3"}


@pytest.mark.asyncio
async def test_to_snake_case_with_special_characters():
    assert to_snake_case("Tag@123") == "Tag@123"


@pytest.mark.asyncio
async def test_split_tags_no_delimiter():
    assert await split_tags("singletag") == {"singletag"}


@pytest.mark.asyncio
async def test_split_tags_with_delimiter_only():
    assert await split_tags(";") == set()


def test_convert_tags_to_semi_colon_basic():
    assert convert_tags_to_semi_colon("tag1 tag2 tag3") == "tag1; tag2; tag3"
    assert convert_tags_to_semi_colon("tag1    tag2") == "tag1; tag2"
    assert convert_tags_to_semi_colon("singleTag") == "singleTag"
    assert convert_tags_to_semi_colon("HTML Parser") == "HTML; Parser"


def test_convert_tags_to_semi_colon_with_extra_spaces():
    assert convert_tags_to_semi_colon(
        "   tag1   tag2   tag3   ") == "tag1; tag2; tag3"
    assert convert_tags_to_semi_colon("  tag1   tag2  ") == "tag1; tag2"
    assert convert_tags_to_semi_colon("   singleTag   ") == "singleTag"


def test_convert_tags_to_semi_colon_empty_string():
    assert convert_tags_to_semi_colon("") == ""
    assert convert_tags_to_semi_colon("    ") == ""
