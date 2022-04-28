using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System.Linq;

public class RotateMenu : MonoBehaviour
{
	List<Button> _buttons=new List<Button>();
	float _appendAngle = 0.0f;
	Vector2 _pos = new Vector2();
	// Use this for initialization
	void Start()
	{
		var children = GetComponentsInChildren<Transform>();
		int childrenNum = 0;
		
		foreach (var obj in children)
		{
			if (obj.tag == "Button")
			{
				var button = obj.GetComponent<Button>();
				_buttons.Add(button);
				++childrenNum;
			}
		}
		_pos = _buttons[0].transform.position;
		foreach (var obj in children)
		{
			if (obj.tag == "Button")
			{
				obj.GetComponent<Button>().onClick.AddListener(() =>
				{
					obj.SetSiblingIndex(children.Length - 1);
					obj.GetComponent<RectTransform>().localScale = new Vector3(1.1f, 1.1f, 1.1f);
				});

			}
		}
	}

	private void RotationMenuUpdate()
	{

		float radius = 100;//半径
		float diff = 0;
		float x = _pos.x;
		float y = _pos.y;
		foreach (var button in _buttons)
		{
			var angle = _appendAngle + diff;
			var pos = button.transform.position;
			pos.x = x + Mathf.Cos(angle) * radius / 2;//Xの半径は半分にしとく
			pos.y = y + Mathf.Sin(angle) * radius;
			var scale = 1.0f + Mathf.Cos(angle) * 0.4f;
			button.transform.localScale = new Vector3(scale, scale, scale);
			button.transform.position = pos;
			diff += (Mathf.PI * 2.0f) / (float)(_buttons.Count);
		}
		var buttons = _buttons.OrderByDescending(a => a.transform.localScale.x);
		//_buttons.Sort((a, b) => (a.transform.localScale.x > b.transform.localScale.x ? -1 : 1));
		foreach (var button in buttons)
		{
			button.transform.SetSiblingIndex(0);
		}
	}

	// Update is called once per frame
	void Update()
	{
		RotationMenuUpdate();
		_appendAngle += 0.001f;

	}

	public void OnTouch()
	{
		Debug.Log("touched");
	}

}
